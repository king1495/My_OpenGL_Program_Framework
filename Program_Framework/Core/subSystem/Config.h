#pragma once
#include "Singleton.h"

class Config final : public Singleton<Config> {
 public:
  Config() { LoadDB(); }
  virtual ~Config() { SaveDB(); }

  void SaveDB() {
    BinaryWriter bw;
    bw.Open(L"./config.dat");

    bw.Close();
  }
  void LoadDB() {
    BinaryReader br;
    if (br.Open(L"./config.dat")) {
      br.Close();
    } else {
      cout << "Load Fail" << endl;
    }
  }

 public:
};