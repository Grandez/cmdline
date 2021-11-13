#pragma once

namespace _jggconfig {

class BaseConfig {
   public:
      virtual void loadConfigFile();
      virtual void writeConfigFile();
      virtual void parseConfigFile();
   protected:
};
}