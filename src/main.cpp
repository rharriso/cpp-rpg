#include <functional>
#include <iostream>
#include <vector>
#include <utility>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

struct stepState {
  const std::string label;
  bool isChecked;
};

// static constexpr auto USAGE =
//   R"(Naval Fate.

//     Usage:
//           naval_fate ship new <name>...
//           naval_fate ship <name> move <x> <y> [--speed=<kn>]
//           naval_fate ship shoot <x> <y>
//           naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
//           naval_fate (-h | --help)
//           naval_fate --version
//  Options:
//           -h --help     Show this screen.
//           --version     Show version.
//           --speed=<kn>  Speed in knots [default: 10].
//           --moored      Moored (anchored) mine.
//           --drifting    Drifting mine.
// )";

int main(/*int argc, [[maybe_unused]]const char **argv*/)
{
  //Use the default logger (stdout, multi-threaded, colored)
  spdlog::info("Starting ImGui + SFML");

  sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  constexpr auto scale_factor = 1.0;
  ImGui::GetStyle().ScaleAllSizes(scale_factor);
  ImGui::GetIO().FontGlobalScale = scale_factor;

  std::vector<stepState> stepStates {
    { "The Plan", true },
    { "Getting started", true },
    { "Finding Errors as Soon as possible", true },
    { "Handling Command Line Parameters", false },
    { "C++ 20 So Far", false },
    { "Reading SFML Input States", false },
    { "Managing Game State", false },
    { "Making Our Game Testable ", false },
    { "Making Game State Allocator Aware", false },
    { "Add Logging To Game Engine", false },
    { "Draw A Game Map", false },
    { "Dialog Trees", false },
    { "Porting from SFML to SDL", false },
  };

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("The Plan");
    auto index = 0;
    for(auto &[label, isChecked] : stepStates) {
      ImGui::Checkbox(fmt::format("{}, {}", index, label).c_str(), &isChecked);
      index++;
    }
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
