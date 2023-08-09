#pragma once

#include <glm/glm.hpp>
#include "utilities.h"
#include "deadPass.h"

namespace {
	GLfloat playerSquare[] = {
		-64.0f, 64.0f, 0.0f,
		64.0f, 64.0f, 0.0f,
		64.0f, -64.0f, 0.0f,
		-64.0f, -64.0f, 0.0f
	};

	int playerSquareIndices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat enemySquare[] = {
		-64.0f, 64.0f, 0.0f,
		64.0f, 64.0f, 0.0f,
		64.0f, -64.0f, 0.0f,
		-64.0f, -64.0f, 0.0f
	};

	int enemySquareIndices[] = {
		0, 1, 2,
		0, 2, 3
	};
}

struct Item {

	// THESE ARE ALL FOR THE MAGE

	// Grey items (bad quality)
	int wornRobe, frayedHat, crackedBracelet, tornBoots, splinteredStaff;
	int rustyChain, damagedCowl, oldBand, leatherSlippers, brittleWand;

	// White items (common quality)
	int cottonRobe, strawHat, woodenBracelet, sturdyBoots, oakStaff;
	int silkRobe, woolHat, ironBracelet, reinforcedBoots, yewStaff;
	int velvetRobe, feltHat, silverBracelet, hardenedBoots, birchStaff;
	int linenRobe, hempHat, bronzeBracelet, paddedBoots, ashStaff;
	int tweedRobe, leatherHat, brassBracelet, lightBoots, pineStaff;

	//green items (uncommon quality)
	int embroideredRobe, wizardHat, enchantedBracelet, mageBoots, magicalStaff;
	int lunarRobe, starHat, moonstoneBracelet, astroBoots, stardustStaff;
	int emberRobe, firebrandHat, flameBracelet, blazeBoots, infernoStaff;
	int windweaverRobe, galeHat, zephyrBracelet, gustBoots, tempestStaff;
	int mysticRobe, seerHat, spiritBracelet, ghostwalkBoots, phantomStaff;

	// Blue items (rare quality)
	int fireApprenticeRobe, fireApprenticeHat, fireApprenticeStaff;
	int aquaSilkRobe, stormCallerHat, earthbinderStaff;
	int celestialRobe, dawnbringerHat, voidtouchedStaff;
	int crystalWeaveRobe, whisperwindHat, luminousStaff;
	int dragonhideRobe, phoenixFeatherHat, wyrmwoodStaff;

	// Purple items (epic quality - Fire skill tree)
	int PrometheusStaff, PrometheusBoots, PrometheusShoulders;

	// Ice skill tree
	int BoreasStaff, BoreasChest, BoreasShoulders, BoreasBracelet, BoreasCrown;

	// Arcane skill tree
	int ArdiusChest, ArdiusShoulders, ArdiusBracelet, ArdiusCrown;

	//THESE ARE ALL FOR THE PALADIN
	//code here
};
struct Enemy {
	int health{};
	int fireResistance{}, arcaneResistance{}, coldResistance{}, shadowResistance{}, physicalResistance{}, poisonResistance{}, natureResistance{};
	glm::vec3 enemyVelocity{};
	glm::vec3 enemyPosition{};
	float enemyWidth{ 64 };
	float enemyHeight{ 64 };

	int enemyQuickAttack{}; //goblin, orc
	int enemyHeavyAttack{}; //orc, ogre
	int enemyStun{}; //ogre
	int enemyPull{}; //ogre
	int enemyWounds{}; //goblin, orc, bleeding attack
	int enemyCripple{}; //orc, slows down opponent
	int enemyShadowstep{}; //goblin, tp to player's back and damaging with a crit
	int enemyCurse{}; //warlock orc cursing player with a hex that does damage over time
	int enemyHeal{}; //goblin shamans heal their allies
	int enemyResistance{}; //goblins shamans give a random resistance boost to one of their allies
	int enemyParalyze{}; //warlock orc fears/paralyzes player for 3 seconds.
	int enemyBomb{}; //goblin throws bomb at you

	GLuint VAO{}, VBO{}, EBO{};

	void createEnemy(GLfloat* vertices, int verticesSize, int* indices, int indicesSize) {
		createVertexArrays(1, VAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, VBO, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, EBO, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

		unbindObjects(VAO);
		unbindObjects(VBO);
		unbindObjects(EBO);
	}
	void drawEnemy() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void collisionEnemy(Enemy* enemy, Object& floor) {
		if (enemy->enemyPosition.y - enemy->enemyHeight < floor.position.y + floor.height) {
			enemy->enemyPosition.y = floor.position.y + floor.height + enemy->enemyHeight;
		}
	}

	void cleanUpEnemy() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}


};

struct Mage {
	int health{};
	int xp{};
	int fireResistance{}, arcaneResistance{}, coldResistance{}, shadowResistance{}, physicalResistance{}, poisonResistance{}, natureResistance{};
	glm::vec3 mageVelocity{};
	glm::vec3 magePosition{};
	float mageWidth{64};
	float mageHeight{64};

	GLuint VAO{}, VBO{}, EBO{};

	void createMage(GLfloat* vertices, int verticesSize, int* indices, int indicesSize) {
		createVertexArrays(1, VAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, VBO, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, EBO, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

		unbindObjects(VAO);
		unbindObjects(VBO);
		unbindObjects(EBO);
	}
	void drawMage() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void collisionMage(Mage* mage, Object& floor) {
		if (mage->magePosition.y - mage->mageHeight < floor.position.y + floor.height) {
			mage->magePosition.y = floor.position.y + floor.height + mage->mageHeight;
		}
	}

	void cleanUpMage() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};