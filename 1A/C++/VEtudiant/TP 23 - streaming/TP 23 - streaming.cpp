/*!
 * \file "TP 23 - streaming.cpp"
 *
 * \brief Programme principal de la simulation de streaming.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#define CIRCULAR_BUFFER_AUTO_ERASE
#include "../TP 23/CircularBuffer.h"
#include "Sender.h"

/**
 * \brief Count UTF-8 characters.
 * 
 * \param str UTF-8 String 
 * \return The number of UTF-8 characters in \c str
 */
size_t strlen_utf8(const std::string& str)
{
  size_t count = 0;
  for (auto& c : str)
  {
    if ((c & 0xC0) != 0x80) {
      count++;
    }
  }
  return count;
}

/**
 * \brief Clean an ill-formed UTF-8 string.
 * 
 * This function replaces all ill-formed UTF-8 characters with some '?' characters. 
 * 
 * \param [in,out] str the string to clean
 */
void strclean_utf8(std::string& str)
{
  size_t nNbSpecialBytes = 0;  //Special bytes are 0b10xxxxxx

  for (auto it = str.begin(); it != str.end();)
  {
    if (((*it) & 0b1110'0000) == 0b1100'0000)
      nNbSpecialBytes = 1;
    else if (((*it) & 0b1111'0000) == 0b1110'0000)
      nNbSpecialBytes = 2;
    else if (((*it) & 0b1111'1000) == 0b1111'0000)
      nNbSpecialBytes = 3;
    else if (((*it) & 0b1000'0000) == 0b1000'0000)
    {
      *it = '?';
      nNbSpecialBytes = 0;
    }
    else
      nNbSpecialBytes = 0;

    bool bBadUTF8 = false;
    for(size_t i = 0; i < nNbSpecialBytes; ++i)
    {
      auto it2 = it;
      if (static_cast<size_t>(std::distance(it, str.end())) < i+1)
      {
        std::fill(it, str.end(), '?');
        return;
      }
      std::advance(it2, i+1);
      if (it2 == str.end() || ((*it2) & 0b1100'0000) != 0b1000'0000)
      {
        std::fill(it, it2, '?');
        it = it2;
        bBadUTF8 = true;
        break;
      }
    }
    if (!bBadUTF8)
      std::advance(it, nNbSpecialBytes);
    if (it != str.end())
      it++;
  }
}

/*!\brief This is the main!
 */
int main()
{
  using namespace std::chrono_literals;
#ifdef _WIN32
  SetConsoleOutputCP(65001);
#endif

  //This is the object that "send" data for streaming. For this simulation, a string is streamed word by word.
  CSender sender;

  //This is the circular buffer used for streaming.
  //TODO : Modifier la ligne suivante pour instancier un buffer circulaire sur des char.
  CCircularBuffer circBuf;

  //this is the buffer that read the circular buffer every 100 ms. 2 bytes at a time.
  std::vector<char> receivedChunk(2);

  //This is the reconstructed stream
  std::vector<char> reconstructedStream;

  //Ask user for the size of the circular buffer
  std::cout << "Please enter the size of the streaming buffer: ";
  size_t nSize;
  std::cin >> nSize;

  //Initialise the circular buffer
  //TODO : Modifier la ligne suivante pour instancier un buffer circulaire sur des char et de la bonne taille.
  //TODO : Gérer également ici le cas potentiel ou l'utilisateur n'a pas entré un nombre égal à une puissance de 2. Le buffer devrait alors lancer une exception.
  circBuf = CCircularBuffer(nSize);

  //This boolean will be true when the stream reaches its end.
  bool bEndOfStream = false;

  //Erase screen
  std::cout << "\x1B[2J";
  bool bBright = false;
  while (!bEndOfStream)
  {
    //Move cursor to top left pos
    std::cout << "\x1B[0;0H\x1B[3;" << (bBright ? "2;" : "") << "32mReceiving data...\x1B[0m\n";
    bBright = !bBright;

    //Simulate new data arriving...
    auto nextPacket = sender.SendNextPacket(circBuf.freeSpace());
    if (nextPacket.empty() && circBuf.usedSpace() == 0)
    {
      std::cerr << "\x1B[1;31m##################################################\n";
      std::cerr << "##################################################\n";
      std::cerr << "##################################################\n";
      std::cerr << "# Buffer is too small to accept the next packet! #\n";
      std::cerr << "##################################################\n";
      std::cerr << "##################################################\n";
      std::cerr << "##################################################\n\x1B[0m";
      bEndOfStream = true;
    }
    circBuf.write(nextPacket);

    //Read a new chunk
    size_t nNbReadElements = circBuf.read(receivedChunk);
    auto itEnd = receivedChunk.begin();
    std::advance(itEnd, nNbReadElements);
    std::cout << "Last chunk is: \x1B[48;2;0;0;175m" << std::string(receivedChunk.begin(), itEnd) << "\x1B[0m\n";
    reconstructedStream.insert(reconstructedStream.end(), receivedChunk.begin(), itEnd);
    if (nNbReadElements != 0 && receivedChunk[nNbReadElements - 1] == '\0')
      bEndOfStream = true;

    //Print raw data currently present in circular buffer
    auto rawData = circBuf.rawData();
    std::replace(rawData.begin(), rawData.end(), char('\0'), char('-'));
    std::string strRawData(rawData.begin(), rawData.end());
    strclean_utf8(strRawData);
    strRawData += std::string(circBuf.size() - strlen_utf8(strRawData), ' ');
    std::cout << "Raw data in circular buffer is: \x1B[48;2;0;0;175m" << strRawData << "\x1B[0m\n";

    //Print "unrolled" content of circular buffer
    std::vector<unsigned char> unrolledBuf;
    circBuf.unrollTo(unrolledBuf);
    std::string strUnrolled(circBuf.size(), ' ');
    std::copy(unrolledBuf.begin(), unrolledBuf.end(), strUnrolled.begin());
    strclean_utf8(strUnrolled);
    strUnrolled += std::string(circBuf.size() - strlen_utf8(strUnrolled), ' ');
    std::cout << "Unrolled circular buffer is: \x1B[48;2;0;0;175m" << strUnrolled << "\x1B[0m\n";

    //Print the reconstructed stream
    std::cout << "Reconstructed data is: \x1B[1;32m" << std::string(reconstructedStream.begin(), reconstructedStream.end()) << "\x1B[0m\n";

    std::this_thread::sleep_for(100ms);
  }

  return 0;
}

