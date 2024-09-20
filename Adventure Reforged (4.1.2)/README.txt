Version-
1.1
Made for GB Studio 4.1.2
Released 16/9/2024, updated 20/9/2024

Description-
Adventure Reforged is an engine plugin that completely replaces the Adventure scene type. It includes the following features:
-More performant player movement
-Smoother diagonal player movement
-Solid actors that the player cannot move through
-Actors pass through each other and the player
-Toggleable background collision
-Toggleable swimming movement

Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'Adventure Reforged' folder that contains this readme file to the 'plugins' folder.
Compile your game.

Useage instructions-
-Note that the player can only move at movement speed 1, as movement speeds are now hardcoded into the scene type. Any events that change the player's move speed will be ignored.
-Solid actors can be created by setting the collision type of an actor to None. Make sure solid actors do not move into the player, or the player will get stuck. Make sure non-solid actors do not overlap solid actors, as this will allow the player to get stuck in solid actors.
-To use toggleable background collision, draw ladder tiles on top of solid collision tiles. The Engine Field Update event can then be used to update the Toggleable Collision engine field and toggle those tiles on and off. Actors will never move through toggleable collision whether it is on or off.
-To use swimming movement, the Engine Field Update event can be used to update the Swimming engine field and toggle it on and off.
-The Actors Pass Through Actors plugin behaviour is included in this plugin, so don't include it in Adventure Reforged projects or it may cause conflicts.

To do-
-Implement better sliding against solid actors.
-Add support for different movement speeds.
-Monitor and potentially improve on performance.

Credits-
Made by Shin
https://gbstudiolab.neocities.org/
Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.