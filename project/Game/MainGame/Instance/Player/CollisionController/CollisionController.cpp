#include "CollisionController.h"

#include <Engine/Module/World/Collision/Collider/SphereCollider.h>
#include <Engine/Module/World/Collision/CollisionManager.h>
#include <Engine/Module/World/WorldInstance/WorldInstance.h>
#include <Engine/Runtime/WorldClock/WorldClock.h>

#define VECTOR3_SERIALIZER
#include <Engine/Resources/Json/JsonSerializer.h>

CollisionController::CollisionController() {
	collider = std::make_shared<SphereCollider>();
	collider->initialize();
	collider->set_active(false);
	collisionManager->register_collider("AttackCollider", collider);
	if (parent) {
		collider->set_parent(*parent.ptr());
	}
	reset();
}

void CollisionController::initialize(JsonResource json) {
	float colliderSize = json.try_emplace<float>("ColliderSize");
#ifdef _DEBUG
	debugValue.colliderSize = colliderSize;
#endif // _DEBUG

	collider->set_radius(colliderSize);
	BeginTime = json.try_emplace<float>("BeginTime");
	EndTime = json.try_emplace<float>("EndTime");
	auto& obj = json.cget();
	if (obj.contains("Curve")) {
		auto& curveJson = obj["Curve"];
		for (auto& val : curveJson.items()) {
			float key = std::stof(val.key());
			Vector3 curveValue = val.value();
			curve.emplace(key, curveValue);
		}
	}
}

void CollisionController::reset() {
	timer = 0;
	next = curve.begin();
}

void CollisionController::update() {
	timer += WorldClock::DeltaSeconds();

	if (timer <= BeginTime) {
		collider->set_active(false);
	}
	else if (timer <= EndTime) {
		collider->set_active(true);
		if (next == curve.end()) {
			return;
		}

		Vector3 nowTranslate;
		if (timer >= next->first) {
			++next;
		}
		if (next == curve.end()) {
			nowTranslate = CVector3::ZERO;
		}
		else if (next == curve.begin()) {
			nowTranslate = next->second;
		}
		else {
			AnimationCurve::const_iterator prev = std::prev(next);
			const float& NextCurveTime = next->first;
			const Vector3& NextTranslate = next->second;
			const float& PrevCurveTime = prev->first;
			const Vector3& PrevTranslate = prev->second;

			float parametric = (timer - PrevCurveTime) / (NextCurveTime - PrevCurveTime);
			nowTranslate = Vector3::Lerp(PrevTranslate, NextTranslate, parametric);
		}
		collider->get_transform().set_translate(nowTranslate);
	}
	else {
		collider->set_active(false);
	}
}

void CollisionController::disable_force() {
	collider->set_active(false);
}

#ifdef _DEBUG
#include <imgui.h>
void CollisionController::debug_gui() {
	ImGui::DragFloat("ColliderSize", &debugValue.colliderSize, 0.1f);
	ImGui::DragFloatRange2("ActiveTime", &BeginTime, &EndTime, 0.01f);

	ImGui::Separator();
	ImGui::DragFloat("Key", &debugValue.key, 0.01f, 0.0f, 100.0f);
	ImGui::DragFloat3("Value", &debugValue.value.x, 0.1f);
	if (ImGui::Button("Add")) {
		curve.emplace(debugValue.key, debugValue.value);
	}
	ImGui::Text("List");
	for (auto itr = curve.begin(); itr != curve.end();) {
		const float& key = itr->first;
		Vector3& value = itr->second;
		ImGui::Text("%.2f:", key);
		ImGui::SameLine();
		ImGui::DragFloat3(std::format("##{}", key).c_str(), &value.x, 0.1f);
		ImGui::SameLine();
		if (ImGui::Button(std::format("Erase##{}", key).c_str())) {
			itr = curve.erase(itr);
			next = curve.begin();
		}
		else {
			++itr;
		}
	}

	ImGui::InputText("Filename", debugValue.file, 128);
	if (ImGui::Button("Save")) {
		if (debugValue.file[0] == '\0') {
			return;
		}
		JsonResource json{ ActionJsonDir / (debugValue.file + std::string(".json")) };
		json.write("ColliderSize", debugValue.colliderSize);
		json.write("BeginTime", BeginTime);
		json.write("EndTime", EndTime);
		nlohmann::json curveJson = nlohmann::json::object();
		for (const auto& [key, value] : curve) {
			curveJson.emplace(std::to_string(key), value);
		}
		json.write("Curve", std::move(curveJson));

		json.save();

		initialize(json);
	}

}
#endif // _DEBUG
