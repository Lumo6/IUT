/*!
 * \file  "prog.cpp"
 *
 * \brief Programme principal. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 */

/*!
 *
 * \mainpage TP 23 - Contrôle
 *
 * Réferrez-vous au sujet en PDF pour les instructions !
 *
 */

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif
#include "CircularBuffer.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <numeric>

/*!
 * \brief Main entry-point for this application. 
 *
 * Point d'entrée principal.
 *
 */
int main(void)
{
#ifdef _WIN32
  SetConsoleOutputCP(65001);
#endif

  BEGIN_TESTS;

  NOTICE("CCircularBufferError exception object tests");
  {
    CCircularBufferError e;
    TEST("Unknown error", e.errorCode(), CCircularBufferError::ErrorCodes::UnknownError);
    TEST("Unknown error", std::string(e.what()), "Unknown error");
    std::stringstream strError;
    strError << e;
    TEST("Test stream output of error", strError.str(), "Error code : UnknownError\n"
         "Description : Unknown error");
  }
  {
    CCircularBufferError e(CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2);
    TEST("The size of the circular buffer is not a power of 2.", e.errorCode(), CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2);
    TEST("The size of the circular buffer is not a power of 2.", std::string(e.what()), "The size of the circular buffer is not a power of 2.");
    std::stringstream strError;
    strError << e;
    TEST("Test stream output of error", strError.str(), "Error code : SizeIsNotPowerOf2\n"
         "Description : The size of the circular buffer is not a power of 2.");
  }
  {
    CCircularBufferError e(CCircularBufferError::ErrorCodes::NotEnoughFreeSpace);
    TEST("The circular buffer is too small.", e.errorCode(), CCircularBufferError::ErrorCodes::NotEnoughFreeSpace);
    TEST("The circular buffer is too small.", std::string(e.what()), "The circular buffer is too small.");
    std::stringstream strError;
    strError << e;
    TEST("Test stream output of error", strError.str(), "Error code : NotEnoughFreeSpace\n"
         "Description : The circular buffer is too small.");
  }
  NOTICE("Construction tests");
  {
    CCircularBuffer defBuf;
    std::vector<unsigned char> stdBuf(1);
    TEST("Default construct CCircularBuffer", defBuf.size(), 0);
    TEST("Default construct CCircularBuffer", defBuf.freeSpace(), 0);
    TEST("Default construct CCircularBuffer", defBuf.usedSpace(), 0);
    TEST("Reading from a default constructed CCircularBuffer", defBuf.read(stdBuf), 0);
    //TODO : Ecrire un test qui vérifie que le code suivant génère bien une exception de type CCircularBufferError :
    //  defBuf.write(stdBuf);
    //Vérifiez à l'aide de tests que l'exception possède les caractéristiques suivantes (en supposant que `e` soit l'objet de type CCircularBufferError) :
    //  e.errorCode() == CCircularBufferError::ErrorCodes::NotEnoughFreeSpace;
  }
  {
    CCircularBuffer buf256(256);
    TEST("CCircularBuffer(256)", buf256.size(), 256);
    TEST("CCircularBuffer(256)", buf256.freeSpace(), 256);
    TEST("CCircularBuffer(256)", buf256.usedSpace(), 0);
  }
  //TODO : Ecrire un test qui vérifie que le code suivant génère bien une exception de type CCircularBufferError :
  //  CCircularBuffer buf(3);
  //Vérifiez à l'aide de tests que l'exception possède les caractéristiques suivantes (en supposant que `e` soit l'objet de type CCircularBufferError) :
  //  e.errorCode() == CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2;

  NOTICE("Read-write tests");
  CCircularBuffer buf16(16);
  std::vector<unsigned char> dataToWrite_10(10);
  std::vector<unsigned char> dataToWrite_6(6);
  std::vector<unsigned char> readData_10(10);
  std::vector<unsigned char> readData_16(16);

  //0 to 9
  std::iota(dataToWrite_10.begin(), dataToWrite_10.end(), 0);
  buf16.write(dataToWrite_10);
  TEST("State after writing 10 elements", buf16.usedSpace(), 10);
  TEST("State after writing 10 elements", buf16.freeSpace(), 16 - 10);
  TEST("Reading 10 elements", buf16.read(readData_10), 10);
  TEST("State after reading 10 elements", readData_10, dataToWrite_10);
  TEST("State after reading 10 elements", buf16.usedSpace(), 0);
  TEST("State after reading 10 elements", buf16.freeSpace(), 16);

  //10 to 19
  std::iota(dataToWrite_10.begin(), dataToWrite_10.end(), 10);
  buf16.write(dataToWrite_10);
  TEST("State after writing 10 elements", buf16.usedSpace(), 10);
  TEST("State after writing 10 elements", buf16.freeSpace(), 16 - 10);
  TEST("Reading 10 elements", buf16.read(readData_10), 10);
  TEST("State after reading 10 elements", readData_10, dataToWrite_10);
  TEST("State after reading 10 elements", buf16.usedSpace(), 0);
  TEST("State after reading 10 elements", buf16.freeSpace(), 16);

  buf16.write(dataToWrite_10);
  std::vector<unsigned char> bigBuffer(256);
  TEST("Trying to read up to 256 elements", buf16.read(bigBuffer), 10);

  buf16.write(dataToWrite_10);
  //TODO : Ecrire un test qui vérifie que le code suivant génère bien une exception de type CCircularBufferError :
  //  buf16.write(dataToWrite_10);
  //Vérifiez à l'aide de tests que l'exception possède les caractéristiques suivantes (en supposant que `e` soit l'objet de type CCircularBufferError) :
  //  e.errorCode() == CCircularBufferError::ErrorCodes::NotEnoughFreeSpace;
  TEST("State of buf16 after trying to write to much data.", buf16.size(), 16);
  TEST("State of buf16 after trying to write to much data.", buf16.usedSpace(), 10);
  TEST("State of buf16 after trying to write to much data.", buf16.freeSpace(), 6);

  buf16.read(bigBuffer);
  std::iota(dataToWrite_10.begin(), dataToWrite_10.end(), 0);//0-9
  std::iota(dataToWrite_6.begin(), dataToWrite_6.end(), 10);//10-15
  buf16.write(dataToWrite_10);
  buf16.write(dataToWrite_6);
  TEST("Read a full buffer.", buf16.usedSpace(), 16);
  TEST("Read a full buffer.", buf16.freeSpace(), 0);
  TEST("Read a full buffer.", buf16.read(readData_16), 16);
  auto valBuf = std::vector<unsigned char>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
  TEST("Read a full buffer.", readData_16, valBuf);

  NOTICE("Unrolling test");
  buf16.write(dataToWrite_10);
  //TODO : Modifiez les deux lignes suivantes de façon à ce que unrolledData et validateUnrolledData soient des vecteurs de int.
  std::vector<unsigned char> unrolledData{ 255 };
  std::vector<unsigned char> validateUnrolledData{ 255 };
  buf16.unrollTo(unrolledData);
  TEST("State of buf16 after unrolling data", buf16.size(), 16);
  TEST("State of buf16 after unrolling data", buf16.freeSpace(), 6);
  TEST("State of buf16 after unrolling data", buf16.usedSpace(), 10);
  std::copy(dataToWrite_10.begin(), dataToWrite_10.end(), std::back_inserter(validateUnrolledData));
  TEST("Validate unrolledData elements", unrolledData, validateUnrolledData);

  NOTICE("Raw data access");
#ifdef _DEBUG
  std::vector<unsigned char> bufVal{ 8, 9, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7 };
#else
  std::vector<unsigned char> bufVal{ 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7 };
#endif
  TEST("Raw data", buf16.rawData(), bufVal);

  END_TESTS;
  return 0;
}

