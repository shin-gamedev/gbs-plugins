# Shin's GB Studio plugins
## Description
Plugins for GB Studio 3.1 and up. Plugins may or may not be compatible with later GB Studio versions.
## How to install
Download the plugins as a ZIP file from the green Code button in the top right.
Further information about installation can be found in each plugin's respective README.txt file.
## License
Plugins licensed under WTFPL, so you can do whatever you like with them. Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.
## Engine plugins
#### Actors Pass Through Actors (4.1.2, 3.2.0, 3.1.0)
This plugin allows for all actors to pass through other actors, including the player, even when collisions are enabled in a move event.
Moving actors will no longer stop moving when colliding with another actor.
This is useful for when you want enemy actors to collide with the player.
Please read the respective README files for specific instructions to the version you are using.
#### Top Down Followers (3.2.0)
This plugin allows 0-3 actors to follow the player in a Top Down scene. The plugin adds an engine field called 'Number of Followers' that can be changed from the settings or at runtime from the 'Engine Field Update' event. The plugin selects that number of actors in the scene as followers, starting with the first actor.
#### Adventure Reforged (4.1.2, 4.0.0)
Adventure Reforged is an engine plugin that completely replaces the Adventure scene type. It includes the following features:
-More performant player movement
-Smoother diagonal player movement
-Solid actors that the player cannot move through
-Actors pass through each other and the player
-Toggleable background collision
-Toggleable swimming movement
#### Shmup Reloaded (4.1.2, 3.2.0)
Shmup Reloaded is an engine plugin that completely replaces the Shoot 'Em Up scene type. It includes the following features:
-Full diagonal 8 way movement for the player with autoscrolling in all 4 directions
-Appropriate animation controller for the player
-Consistent 8px by 8px collisions for the player regardless of their collision box, allowing the player to use a smaller collision box for a better feeling shmup
-All triggers activate when they are scrolled onto the screen rather than when the player touches them (checked at the top of the screen for horizontal scrolling and the left of the screen for vertical scrolling)
-Better collision for higher movement speeds
#### Talking Actors (4.1.2)
An engine plugin that changes an actor's animation while dialogue is being drawn, useful for animating talking characters during cutscenes.
## Event plugins
#### Background Dialogue (3.2.0)
An event plugin that allows you to easily make dialogue boxes using backgrounds in GB Studio. It's suitable for making standalone visual novel style scenes and cutscenes. Features include:
-Positionable name tags
-Multiple boxes of positionable dialogue
-Automatic line spacing
-Prompt when dialogue is complete (uses bottom right tile of font)
#### Repaint Background (3.2.0)
An event plugin that allows you to repaint the background with the original scene background, removing any background text or dialogue from the screen.
#### Load Sprite (3.1.0)
This plugin loads a sprite into memory in the current scene.
It does not compile to any GBVM instructions.
It only tells the GBS compiler to include the sprite in the current scene.
The sprite can then be referenced by engine code, such as when dynamically loading projectiles.