#pragma once
#include "config.hpp"

void showHelpSimple    (HelpRequested* help);
void showHelpDetail    (HelpRequested* help);
void showHelp          (HelpRequested *help);
void printOption       (Options& options, string option);
void showCurrentConfig ();

