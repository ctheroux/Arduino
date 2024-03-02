/*************************************************************************************
 *
 * Arduino EEPROM content display
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
#include "EEPROMDump.h"

void setup() {
  Serial.begin(9600);

  EEPROMDump dump(23, 56);
  dump.dump();
}

void loop() {
}

