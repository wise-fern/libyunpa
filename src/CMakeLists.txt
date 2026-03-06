target_sources(
  ${PROJECT_NAME}
  PRIVATE "Engine/Core.cpp"
          "Engine/EventManager.cpp"
          "Engine/Scene.cpp"
          "Engine/SceneManager.cpp"
          "Graphics/Menu.cpp"
          "Graphics/TextOptions.cpp"
          "System/Time.cpp"
          "System/Utils.cpp"
  PUBLIC FILE_SET
         CXX_MODULES
         FILES
         "libyunpa.cppm"
         "Engine/Core.cppm"
         "Engine/EventManager.cppm"
         "Engine/Scene.cppm"
         "Engine/SceneManager.cppm"
         "Graphics/Menu.cppm"
         "Graphics/TextOptions.cppm"
         "System/Events.cppm"
         "System/KeyBind.cppm"
         "System/Time.cppm"
         "System/Utils.cppm")
if(WIN32)
  target_sources(
    ${PROJECT_NAME}
    PRIVATE "System/Windows.cpp"
    PUBLIC FILE_SET CXX_MODULES FILES "System/Windows.cppm")
else()
  target_sources(
    ${PROJECT_NAME}
    PRIVATE "System/Linux.cpp"
    PUBLIC FILE_SET CXX_MODULES FILES "System/Linux.cppm")
endif()
