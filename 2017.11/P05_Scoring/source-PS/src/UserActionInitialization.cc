//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UserActionInitialization.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "UserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "EventAction.hh"
//#include "SteppingAction.hh"
#include "RunAction.hh"

//------------------------------------------------------------------------------
  UserActionInitialization::UserActionInitialization()
  : G4VUserActionInitialization()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  UserActionInitialization::~UserActionInitialization()
//------------------------------------------------------------------------------
{}

// EventAction イベントごとのヒスト記入  
// RunAction  ヒストグラムの準備と書き出し用ファイルの操作
//------------------------------------------------------------------------------
  void UserActionInitialization::Build() const
//------------------------------------------------------------------------------
{
    EventAction* eventaction = new EventAction();
    SetUserAction( new PrimaryGenerator() );
    SetUserAction(eventaction);
//    SetUserAction( new SteppingAction(eventaction) );　　不要
    SetUserAction(new RunAction);
}




