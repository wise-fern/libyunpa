export module libyunpa;

// Engine partitions
export import :Core;
export import :EventManager;
export import :Scene;
export import :SceneManager;

// Graphics partitions
export import :Menu;

// System partitions
export import :Events;
export import :KeyBind;
export import :Time;
export import :Utils;

// Utility partitions
export import :Menu;
export import :TextOptions;

#ifdef WIN32
export import :Windows;
#else
export import :Linux;
#endif
