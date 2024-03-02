/*************************************************************************************
 *
 * Arduino EEPROM content display definition file
 *
 *************************************************************************************
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT
 * HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * IT IS NOT PERMITTED TO MODIFY THIS COMMENT BLOCK.
 *
 * (c)2024, Claude "Tryphon" Theroux, Montreal, Quebec, Canada
 * http://www.ctheroux.com/
 *
 ************************************************************************************/

#include <Arduino.h>
#include <EEPROM.h>
#include "EEPROMDump.h"

EEPROMDump::EEPROMDump(unsigned int pFrom, unsigned int pTo) {
  from = pFrom;
  to = pTo;
}

EEPROMDump::~EEPROMDump() {
}

void EEPROMDump::put8BytesSeparator(unsigned int pByteIndex) {
  if( pByteIndex == 8 ) {
    Serial.print(F(" "));
  }
}

void EEPROMDump::putEEPROMByte(unsigned int pAddress) {
  char hexToASCII[17] = { "0123456789abcdef" };

  if( pAddress < EEPROM.length() ) {
    int value = EEPROM.read(pAddress);
    Serial.print(hexToASCII[(value & 0xf0) >> 4]);
    Serial.print(hexToASCII[(value & 0xf)]);
    Serial.print(F(" "));
  } else {
    Serial.print(F("   "));
  }  
}

void EEPROMDump::putEEPROMByteAsChar(unsigned int pAddress) {
  if( pAddress < EEPROM.length() ) {
    int value = EEPROM.read(pAddress);
    if( isPrintable(value) ) {
      Serial.print(F(" "));
      Serial.print((char) value);
    } else {
      Serial.print(F(" ."));
    }
  } else {
      Serial.print(F("  "));
  }
}

void EEPROMDump::dumpEEPROM() {
  char buffer [16];
  Serial.println(F("EEPROM Dump"));
  Serial.println("");
  Serial.println(F("        0  1  2  3  4  5  6  7   8  9  a  b  c  d  e  f"));

  for( unsigned int i = from - (from % 16); i < to; i += 16 ) {
    sprintf(buffer, "0x%04x ", i);
    Serial.print(buffer);
    for( unsigned int j = 0; j < 16; ++j ) {
      put8BytesSeparator(j);
      putEEPROMByte(i + j);
    }
    Serial.print(" ");
    for( unsigned int j = 0; j < 16; ++j ) {
      put8BytesSeparator(j);
      putEEPROMByteAsChar(i + j);
    }
    Serial.println("");
  }
}

void EEPROMDump::writeAddressRange(const char *pLabel, unsigned long pFrom, unsigned long pTo) {
  
  char buffer[64];

  sprintf(buffer, "%-8s: 0x%04lx - 0x%06lx (%lu KB)", pLabel, pFrom, pTo, (pTo - pFrom + 1) / 1024);
  Serial.println(buffer);
}

void EEPROMDump::dump() {
  Serial.println(F("\n\nArduino EEPROM content display, v01.00"));
  Serial.println(F("======================================"));
  Serial.println("");

  #if defined(FLASHEND) || defined(RAMSTART) || defined(RAMEND) || defined(E2END)
    displayMemoryConfiguration();
  #endif

  dumpEEPROM();
}

#if defined(FLASHEND) && defined(RAMSTART) && defined(RAMEND) && defined(E2END)
void EEPROMDump::displayMemoryConfiguration() {
    #if defined(FLASHEND)
        writeAddressRange("FLASH:", 0, FLASHEND);
    #endif
    #if defined(RAMSTART) && defined(RAMEND)
        writeAddressRange("RAM:", RAMSTART, RAMEND);
    #endif
    #if defined(E2END)
        writeAddressRange("EEPROM:", 0, E2END);
    #endif
    Serial.println("");    
}

#endif
