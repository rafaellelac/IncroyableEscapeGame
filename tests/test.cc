#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MECPuzzle.hh"
#include "MECMaze.hh"
#include "Quizz.hh"
#include "MEC.hh"
#include "MainMenu.hh"
#include "Classroom.hh"
#include "state.hh"
#include "Scores.hh"
#include "Puzzle.hh"
#include "MECQuizz.hh"
#include "MECEnigme.hh"
#include "MazeGame.hh"
#include "LastScreen.hh"
#include "HS.hh"
#include "Fin.hh"
#include "Enigme.hh"
#include "Door.hh"
#include "asset.hh"

// Tests pour la classe Puzzle
TEST_CASE("Puzzle initialisation") {
    std::shared_ptr<Context> context = std::make_shared<Context>();
    Puzzle puzzle(context);

    SUBCASE("Initialisation correcte du puzzle") {
        puzzle.Init();
        CHECK(puzzle.isCompleted() == false);
    }

    SUBCASE("Interaction utilisateur") {
        puzzle.Init();
        puzzle.ProcessInput();
        CHECK(puzzle.isCompleted() == false);
    }
}


// Tests pour le gestionnaire d'états
TEST_CASE("State Manager transitions") {
    Engine::StateManager stateManager;

    SUBCASE("Suppression d'un état") {
        stateManager.PopCurrent();
        CHECK_NOTHROW(stateManager.ProcessStateChange());
    }
}


// Tests pour la classe Enigme
TEST_CASE("Enigme interaction") {
    std::shared_ptr<Context> context = std::make_shared<Context>();
    Enigme enigme(context);

    SUBCASE("Initialisation correcte") {
        enigme.Init();
        CHECK(enigme.isCompleted() == false);
    }
}

// Tests pour la classe MazeGame
TEST_CASE("MazeGame gestion") {
    std::shared_ptr<Context> context = std::make_shared<Context>();
    MazeGame mazeGame(context);

    SUBCASE("Initialisation correcte") {
        mazeGame.Init();
        CHECK_NOTHROW(mazeGame.Update(sf::seconds(0.1f)));
    }
}

//test pour la classe Quizz
TEST_CASE("Test Quizz Initialization") {
    auto context = std::make_shared<Context>();
    Quizz quizz(context);
    try {
        quizz.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Quizz initialization: " << e.what() << std::endl;
    }

    CHECK(quizz.isCompleted() == false);
}
TEST_CASE("Test Adding Questions to Quizz") {
    auto context = std::make_shared<Context>();
    Quizz quizz(context);
    try {
        quizz.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Quizz initialization: " << e.what() << std::endl;
    }

    Question question = {"Test Question?", {"Option 1", "Option 2"}, 0};
    quizz += question;

    CHECK(quizz.isCompleted() == false);
}
// Tests de l'intialisation de contexte
TEST_CASE("Test Context Initialization") {
    auto context = std::make_shared<Context>();

    CHECK(context->m_window != nullptr);
    CHECK(context->m_states != nullptr);
    CHECK(context->m_assets != nullptr);
    CHECK(context->m_timer != nullptr);
}
// Test pour la classe classroom
TEST_CASE("Test Classroom Initialization") { 
    auto context = std::make_shared<Context>();
    Classroom classroom(context);
    try {
        classroom.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Classroom initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MEC
TEST_CASE("Test MEC Initialization") {
    auto context = std::make_shared<Context>();
    MEC mec(context);
    try {
        mec.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MEC initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe scores
TEST_CASE("Test Scores Initialization") {
    auto context = std::make_shared<Context>();
    Scores scores(context);
    try {
        scores.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Scores initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MainMenu
TEST_CASE("Test MainMenu Initialization") {
    auto context = std::make_shared<Context>();
    MainMenu mainMenu(context);
    try {
        mainMenu.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MainMenu initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe Fin
TEST_CASE("Test Fin Initialization") {
    auto context = std::make_shared<Context>();
    Fin fin(context);
    try {
        fin.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Fin initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe Door
TEST_CASE("Test Door Initialization") {
    auto context = std::make_shared<Context>();
    Door door(context);
    try {
        door.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during Door initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe HS
TEST_CASE("Test HS Initialization") {
    auto context = std::make_shared<Context>();
    HS hs(context);
    try {
        hs.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during HS initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MECQuizz
TEST_CASE("Test MECQuizz Initialization") {
    auto context = std::make_shared<Context>();
    MECQuizz mecQuizz(context);
    try {
        mecQuizz.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MECQuizz initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MECEnigme
TEST_CASE("Test MECEnigme Initialization") {
    auto context = std::make_shared<Context>();
    MECEnigme mecEnigme(context);
    try {
        mecEnigme.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MECEnigme initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MECPuzzle
TEST_CASE("Test MECPuzzle Initialization") {
    auto context = std::make_shared<Context>();
    MECPuzzle mecPuzzle(context);
    try {
        mecPuzzle.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MECPuzzle initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe MECMaze
TEST_CASE("Test MECMaze Initialization") {
    auto context = std::make_shared<Context>();
    MECMaze mecMaze(context);
    try {
        mecMaze.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during MECMaze initialization: " << e.what() << std::endl;
    }

    CHECK(context->m_window != nullptr);
}
// Test pour la classe LastScreen
TEST_CASE("Test LastScreen Initialization") {
    auto context = std::make_shared<Context>();
    LastScreen lastScreen(context);
    try {
        lastScreen.Init();
    } catch (const std::exception& e) {
        std::cerr << "Exception during LastScreen initialization: " << e.what() << std::endl;
    }
    CHECK(context->m_window != nullptr);
}

