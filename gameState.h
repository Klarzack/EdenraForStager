#pragma once

enum GameState {
	gameMenu,
	gameRunning,
	gameOptions,
	gameEditor
};

GameState gameState = gameMenu;