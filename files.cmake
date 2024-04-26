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
        Component/Collider.cpp
        Component/Healthbar.cpp
        Component/ImageObject.cpp
        Component/Phase.cpp
        Component/Rockman.cpp
        Component/Scorebar.cpp
        Component/TestBox.cpp
        Component/TileMap.cpp
        Component/SceneManager.cpp
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
        Component/Backgroundmap.hpp
        Component/Collider.hpp
        Component/Healthbar.hpp
        Component/ImageObject.hpp
        Component/Phase.hpp
        Component/Rockman.hpp
        Component/Scorebar.hpp
        Component/TestBox.hpp
        Component/TileMap.hpp
        Component/SceneManager.hpp

        #other
        IncludeComponent.hpp
)

set(TEST_FILES
)
