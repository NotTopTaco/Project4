cmake_minimum_required(VERSION 3.20)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h MatcherAutomaton.h MatcherAutomaton.cpp IDAutomaton.h IDAutomaton.cpp LCommentAutomaton.h LCommentAutomaton.cpp CharMatcherAutomaton.h CharMatcherAutomaton.cpp StringAutomaton.h StringAutomaton.cpp BlkCommentAutomaton.h BlkCommentAutomaton.cpp Parser.h Parser.cpp DatalogProgram.h Parameter.h Predicate.h Rule.h Database.h Relation.h Header.h Tuple.h Interpreter.h)
