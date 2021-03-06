/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <list>
#include <string>

//-- Forward class declarations.
class Option
{
public:
  enum EType {
    eBoolean,
    eCharacter,
    eInteger,
    eList
  };
    
  //---- Constructors
  // For arguments which have no switch char but appear in a special order.
  Option(int aOrder, const char *&aCharPtr, const char *aUsage,
    const char *aArgDesc, bool aRequired = true);
  
  // For arguments which have no switch char but appear in a special order.
  Option(int aOrder, int &aIntRef, const char *aUsage,
    const char *aArgDesc, bool aRequired = true);
    
  // For the rest of the argumets as in a file list.
  Option(std::list<std::string> &aList, const char *aUsage,
   const char *aArgDesc, bool aRequired = true, bool aExpand = false);

  // Given an agument with a switch char ('-') <name> 
  Option(const char *aName, const char *&aCharPtr, const char *aUsage,
   const char *aArgDesc, bool aRequired = false, bool aIgnoreCase = false);
  
  // Given an agument with a switch char ('-') <name> 
  Option(const char *aName, bool &aBoolRef, const char *aUsage,
   bool aArgument = false, const char *aArgDesc = NULL,
   bool aRequired = false, bool aIgnoreCase = false);
  
  // Given an agument with a switch char ('-') <name> 
  Option(const char *aName, int &aIntRef, const char *aUsage,
   const char *aArgDesc, bool aRequired = false, bool aIgnoreCase = false);

  // Given an agument with a switch char ('-') <name> 
  Option(const char *aName, std::list<std::string> &aList, const char *aUsage,
   const char *aArgDesc, bool aRequired = false,
   bool aExpand = false, bool aIgnoreCase = false);

  // Accept member-wise copy
  // Option(const Option &aOption);
  
  //---- Destructor
  ~Option();

  EType getType() const { return type_; }
  const char *getName() const { return name_; }
  const char *getUsage() const { return usage_; }
  const char *getArgDesc() const { return argDesc_; }
  int getOrder() const { return order_; }
  bool ignoreCase() const { return ignoreCase_; }
  bool hasArgument() const { return argument_; }
  bool hasSwitch() const { return switch_; }
  bool isRequired() const { return required_; }
  bool isSet() const { return isSet_; }

  const char *getCharPtr() const  { return charPtrPtr_ != 0 ? *charPtrPtr_ : 0; }
  bool getBool() const { return boolPtr_ != 0 ? *boolPtr_ : false; }
  int getInt() const { return intPtr_ != 0 ? *intPtr_ : -1; }
  const std::list<std::string> &getList() const { return *list_; }
  bool operator<(Option &aOther);
  
  bool setValue(const char *aCp);

protected:
  void expandFiles(const char *aFileName);
    
protected:
  const char  *name_;
  const char **charPtrPtr_;
  bool *boolPtr_;
  int *intPtr_;
  std::list<std::string>   *list_;
  EType type_;
  int order_;
  bool required_;
  bool argument_;
  bool ignoreCase_;
  bool switch_;
  const char *usage_;
  bool isSet_;
  bool expand_;
  const char *argDesc_;
  
  friend class OptionsList;
};

class OptionsList : public std::list<Option>
{
public:
  //---- Constructors
  OptionsList();
  OptionsList(Option *aOptionList[]);

  //---- Destructor
  virtual ~OptionsList();
  
  void addOption(Option &aOption);

  int parse(int &aArgc, const char **aArgv);
  void usage();
  void setOwnsOptions(bool aFlag = true) { ownsOptions_ = aFlag; }
  void append(Option *aOption) { push_back(*aOption); }

protected:
  void getArg(const char **&aArgv, int &aArgc, Option *aOpt, const char *aAt);
  bool find(const char *aopt, Option *&aOption);
  bool find(int aOrder, Option *&aOption);
  void setOpt(Option *aOption, const char *aCp);
  
protected:
  const char *program_;
  int  unswitched_;
  bool ownsOptions_;
};

// ------------------------ Inline Methods ------------------------------
// #include <Options.inl>

#endif // Options_H


