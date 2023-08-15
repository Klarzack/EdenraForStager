#pragma once

enum GameState {
	gameMenu,
	gameEditor,
	gameOptions,
	gameRunning
};

GameState gameState = gameEditor;