#include "hacks/visuals_player.hpp"
#include "hacks/replayinterface.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string VisualsPlayer::getCategory()
{
	return std::string("Visuals");
}

std::string VisualsPlayer::getName()
{
	return std::string("Player");
}

void draw_bones(CPlayerBones bones) {
	Vector3 bone_positions[][2] = {
		{ bones.HEAD, bones.NECK },

		{ bones.NECK, bones.RIGHT_UPPER_ARM },
		{ bones.RIGHT_FOREARM, bones.RIGHT_UPPER_ARM },
		{ bones.RIGHT_FOREARM, bones.RIGHT_HAND },

		{ bones.NECK,  bones.LEFT_UPPER_ARM },
		{ bones.LEFT_FOREARM, bones.LEFT_UPPER_ARM },
		{ bones.LEFT_FOREARM, bones.LEFT_HAND },

		{ bones.NECK, bones.SPINE3 },
		{ bones.SPINE3, bones.SPINE2 },
		{ bones.SPINE2, bones.SPINE1 },
		{ bones.SPINE1, bones.SPINE_ROOT },

		{ bones.SPINE_ROOT, bones.RIGHT_THIGH },
		{ bones.RIGHT_THIGH, bones.RIGHT_CALF },
		{ bones.RIGHT_CALF, bones.RIGHT_FOOT },

		{ bones.SPINE_ROOT, bones.LEFT_THIGH},
		{ bones.LEFT_THIGH, bones.LEFT_CALF},
		{ bones.LEFT_CALF, bones.LEFT_FOOT },
	};

	int arrSize = sizeof(bone_positions) / sizeof(bone_positions[0]);
	for (size_t i = 0; i < arrSize; i++) {

		Vector3 bone3d = bone_positions[i][0];
		Vector2 bone2d = functions::world_to_screen_vec(bone3d);

		Vector3 bone3d1 = bone_positions[i][1];
		Vector2 bone2d1 = functions::world_to_screen_vec(bone3d1);

		if ((bone2d.y < Nemo::Instance().vScreen.y) && (bone2d.x < Nemo::Instance().vScreen.x))
			if ((bone2d1.y < Nemo::Instance().vScreen.y) && (bone2d1.x < Nemo::Instance().vScreen.x))
				if ((bone2d.y > 5 && bone2d.x > 5) && (bone2d1.x > 5 && bone2d1.y > 5))
					utils::render::draw_line(bone2d.x, bone2d.y, bone2d1.x, bone2d1.y, 255, 255, 255, 255);
	}
}

void VisualsPlayer::Tick()
{
	//Log::Debug("vp tick");
	for (int i = 0; i < 255; i++) {
		auto* nPed = &Replayinterface::Instance().peds[i];
		if (nPed == NULL) continue;

		if (!IsValidPtr(nPed) || !IsValidPtr(nPed->ped) || !IsValidPtr(nPed->player)) continue;

		CObject* ped = nPed->ped;
		if (ped == NULL || !IsValidPtr(ped)) continue;

		CRemotePlayer* player = nPed->player;
		if (player == NULL || !IsValidPtr(player)) continue;

		//auto Distance = functions::get_distance(functions::get_local()->fPosition, ped->fPosition);
		//int dif = (int)Distance / 50;
		//int fontSize = 18 - dif <= 2 ? 2 : (18 - dif);
		Vector2 player_pos = functions::world_to_screen_vec(ped->fPosition);

		std::string player_name = functions::get_name_from_index(player->iHandle);
		utils::render::draw_text(player_pos.x - (ImGui::CalcTextSize(player_name.c_str()).x / 2), player_pos.y + 23, functions::get_name_from_index(player->iHandle));

		draw_bones(nPed->bones);
	}
}