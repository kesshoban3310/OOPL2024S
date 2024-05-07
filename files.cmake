set(SRC_FILES
        # Phases
        PhaseTitle.cpp
        PhaseMenu.cpp
        PhaseStage.cpp
        PhaseLose.cpp
        PhaseEndingAnimation.cpp

        # Components
        Component/App.cpp
        Component/Ammo.cpp
        Component/AnimatedObject.cpp
        Component/Backgroundmap.cpp
        Component/Bombombomb.cpp
        Component/Blaster.cpp
        Component/Collider.cpp
        Component/HealthBar.cpp
        Component/ImageObject.cpp
        Component/OctopusBattery.cpp
        Component/Phase.cpp
        Component/Rockman.cpp
        Component/Scorebar.cpp
        Component/SceneManager.cpp
        Component/ScrewDriver.cpp
        Component/TestBox.cpp
        Component/TileMap.cpp
        Component/TileBox.cpp
)

set(INCLUDE_FILES
        # Phases
        PhaseTitle.hpp
        PhaseMenu.hpp
        PhaseStage.hpp
        PhaseLose.hpp
        PhaseEndingAnimation.hpp

        # Components
        Component/App.hpp
        Component/Ammo.hpp
        Component/AnimatedObject.hpp
        Component/Blaster.hpp
        Component/Bombombomb.hpp
        Component/Backgroundmap.hpp
        Component/Collider.hpp
        Component/EnemyAttribute.hpp
        Component/HealthBar.hpp
        Component/ImageObject.hpp
        Component/OctopusBattery.hpp
        Component/Phase.hpp
        Component/Rockman.hpp
        Component/Scorebar.hpp
        Component/SceneManager.hpp
        Component/ScrewDriver.hpp
        Component/TestBox.hpp
        Component/TileMap.hpp
        Component/TileBox.hpp

        #other
        IncludeComponent.hpp
)

set(TEST_FILES
)
