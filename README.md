# Shin's GB Studio plugins
## Description
Plugins for GB Studio 3.1 and up.
## How to install
Download the plugins as a ZIP file from the green Code button in the top right.
Further information about compatibility and installation can be found in each plugin's respective README.txt file.
## License
Plugins licensed under WTFPL, so you can do whatever you like with them. Attribution to Shin or shintendo.neocities.org in credits is appreciated, but not necessary.
## Plugins
#### Engine plugin- actors pass through actors (3.1.0)
This plugin allows for all actors to pass through other actors, including the player, even when collisions are enabled in a move event.
Moving actors will no longer stop moving when colliding with another actor.
This is useful for when you want enemy actors to collide with the player.
The only edit this plugin makes is commenting out the actor collision checks in vm_actor.c.
I may add options for collision with specific collision groups in the future.
Without plugin:
![pass_before](https://user-images.githubusercontent.com/127167977/223601512-28c288fc-62ca-4280-aa4b-bd02572e59cc.gif)
With plugin:
![pass_after](https://user-images.githubusercontent.com/127167977/223601523-768a76b6-0750-4d42-a824-983972bfdfb2.gif)
