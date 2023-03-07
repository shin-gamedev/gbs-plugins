-Version-
1.0
For GB Studio 3.1.0
7/3/2023

-Description-
This plugin allows for all actors to pass through other actors including the player.
Moving actors will no longer stop moving when colliding with another actor.
This is useful for when you want enemy actors to collide with the player.
The only edit this plugin makes is commenting out the actor collision checks in vm_actor.c.
I may add options for collision with specific collision groups in the future.

-Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'EnginePluginActorsPassThroughActors' folder that contains this readme file to the 'plugins' folder.
Reopen your project in GB Studio and compile your game.

-Credits-
Made by Shin
shintendo.neocities.org
Attribution to Shin or shintendo.neocities.org in credits is appreciated, but not necessary.