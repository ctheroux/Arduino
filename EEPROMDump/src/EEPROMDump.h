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

#ifndef __EEPROM_DUMP_H
#define __EEPROM_DUMP_H

class EEPROMDump {

    public:
        EEPROMDump(unsigned int pFrom, unsigned int pTo);
        ~EEPROMDump();

        void dump();

    private:
        unsigned int from;
        unsigned int to;

        void displayMemoryConfiguration();
        void dumpEEPROM();
        void put8BytesSeparator(unsigned int pByteIndex);
        void putEEPROMByte(unsigned int pAddress);
        void putEEPROMByteAsChar(unsigned int pAddress);
        void writeAddressRange(const char *pLabel, unsigned long pFrom, unsigned long pTo);
};

#endif // __EEPROM_DUMP_H