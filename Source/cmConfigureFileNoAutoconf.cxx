/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include "cmConfigureFileNoAutoconf.h"

// cmConfigureFileNoAutoconf
bool cmConfigureFileNoAutoconf::Invoke(std::vector<std::string>& args)
{
  if(args.size() != 2 )
    {
    this->SetError("called with incorrect number of arguments, expected 2");
    return false;
    }
  m_InputFile = args[0];
  m_OuputFile = args[1];
  return true;
}

void cmConfigureFileNoAutoconf::FinalPass()
{
#ifdef CMAKE_HAS_AUTOCONF
  return;
#else  
  m_Makefile->ExpandVariblesInString(m_InputFile);
  m_Makefile->ExpandVariblesInString(m_OuputFile);
  std::ifstream fin(m_InputFile.c_str());
  if(!fin)
    {
    cmSystemTools::Error("Could not open file for read in copy operatation",
                         m_InputFile.c_str());
    return;
    }
  std::ofstream fout(m_OuputFile.c_str());
  if(!fout)
    {
    cmSystemTools::Error("Could not open file for write in copy operatation", 
                         m_OuputFile.c_str());
    return;
    }
  // now copy input to output and expand varibles in the
  // input file at the same time
  const int bufSize = 4096;
  char buffer[bufSize];
  std::string inLine;
  while(fin)
    {
    fin.getline(buffer, bufSize);
    inLine = buffer;
    m_Makefile->ExpandVariblesInString(inLine);
    fout << inLine << "\n";
    }
#endif
}

  
