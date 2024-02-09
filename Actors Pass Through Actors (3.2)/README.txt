Version-
2.0
Made for GB Studio 3.2.0
Released 7/3/2023
Updated 9/2/2024

Description-
This plugin allows for all actors to pass through other actors, including the player, even when collisions are enabled in a move event.
Moving actors will no longer stop moving when colliding with another actor.
This is useful for when you want enemy actors to collide with the player.
The only edit this plugin makes is commenting out the actor collision checks in vm_actor.c.
I may add options for collision with specific collision groups in the future.

Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'Actors Pass Through Actors' folder that contains this readme file to the 'plugins' folder.
Reopen your project in GB Studio and compile your game.

Credits-
Made by Shin
https://gbstudiolab.neocities.org/
Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.