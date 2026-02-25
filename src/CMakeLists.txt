target_sources(
  ${PROJECT_NAME}
  PUBLIC FILE_SET
         CXX_MODULES
         FILES
         "libyunpa.cppm"
         "Engine/Scene.cppm"
         "Engine/SceneManager.cppm"
         "System/Events.cppm"
         "System/Time.cppm"
  PRIVATE "Engine/Core.cpp")
