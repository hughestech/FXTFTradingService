#pragma once

class CCSVFile: public CStdioFile
{

public:

  enum Mode { modeRead, modeWrite };
  CCSVFile(LPCTSTR lpszFilename, Mode mode = modeRead);
  CCSVFile(LPCTSTR lpszFilename, int aMode);
  CCSVFile(void);
  ~CCSVFile(void);

  bool ReadData(CStringArray &arr);
  void WriteData(CStringArray &arr);

#ifdef _DEBUG

  Mode m_nMode;

#endif

};

