
set (SRC
	Audio.cpp
	Enemy.cpp
	Engine.cpp
	Entity.cpp
	Gem.cpp
	Gold.cpp
	Heart.cpp
	Humanoid.cpp
	Input.cpp
	Item.cpp
	Key.cpp
	Level.cpp
	Object.cpp
	PCH.cpp
	Player.cpp
	Potion.cpp
	Projectile.cpp
	Slime.cpp
	SoundBufferManager.cpp
	Sprite.cpp
	TextureManager.cpp
	Torch.cpp
	Transform.cpp
	core/SceneNode.cpp
	core/World.cpp
	../include/modules/imgui/imgui.cpp
	../include/modules/imgui/imgui_draw.cpp
	../include/modules/imgui/imgui-SFML.cpp)

build(roguengine SOURCES ${SRC})
