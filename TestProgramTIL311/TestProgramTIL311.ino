/*************************************************************************************
 *
 * TIL311 Hex Display Test Program
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
 * (c)2022, Claude "Tryphon" Theroux, Montreal, Quebec, Canada
 * http://www.ctheroux.com/
 *
 ************************************************************************************/

/*
 * Wiring
 * 
 * TIL311 Arduino
 *   
 *   1 -->  VCC
 *   2 -->  5       Input B
 *   3 -->  4       Input A
 *   4 -->  8       Left decimal (THROUGH A 220 OHMS RESISTOR)
 *   5 -->  10      Strobe
 *   7 -->  GND 
 *   8 -->  11      Blanking
 *  10 -->  9       Right decimal (THROUGH A 220 OHMS RESISTOR)
 *  12 -->  7       Input D
 *  13 -->  6       Input C
 *  14 -->  VCC 
 *   
 *   6, 9, 11       Not connected
 */

#define INPUTA    4
#define INPUTB    5
#define INPUTC    6
#define INPUTD    7

#define LDECIMAL  8
#define RDECIMAL  9

#define STROBE    10
#define BLANKING  11

void displayDigit(int iDigit) {
  digitalWrite(BLANKING, HIGH);
  digitalWrite(INPUTA, (iDigit & 0x1));
  digitalWrite(INPUTB, (iDigit & 0x2) >> 1);
  digitalWrite(INPUTC, (iDigit & 0x4) >> 2);
  digitalWrite(INPUTD, (iDigit & 0x8) >> 3);
  digitalWrite(BLANKING, LOW);  
}

void testPoints() {
  digitalWrite(BLANKING, HIGH);
  digitalWrite(STROBE, LOW);
  Serial.println("Lighting the left decimal point");
  digitalWrite(LDECIMAL, LOW);
  delay(3000);
  digitalWrite(LDECIMAL, HIGH);
  Serial.println("Left decimal test completed.");
  Serial.println("Lighting the right decimal point");
  digitalWrite(RDECIMAL, LOW);
  delay(3000);
  digitalWrite(RDECIMAL, HIGH);
  Serial.println("Right decimal test completed.");
}

void testDigits() {
  Serial.println("Starting the digits");
  digitalWrite(STROBE, LOW);
  for( int i = 0; i < 16; ++i ) {
    displayDigit(i);
    delay(2000);
  }
  digitalWrite(BLANKING, HIGH);
  Serial.println("Digits test completed.");
}

void testBlanking() {
  Serial.println("Starting the blanking test");
  digitalWrite(STROBE, LOW);
  displayDigit(15);
  digitalWrite(BLANKING, LOW);
  Serial.println(">> Display ON");
  delay(2000);
  digitalWrite(BLANKING, HIGH);
  Serial.println(">> Display OFF");
  delay(2000);
  digitalWrite(BLANKING, LOW);
  Serial.println(">> Display ON");
  delay(2000);
  digitalWrite(BLANKING, HIGH);
  Serial.println(">> Display OFF");
  Serial.println("Blanking test completed.");
}

void testStrobe() {
  Serial.println("Starting the strobe test");
  Serial.println(">> Displaying 8");
  digitalWrite(STROBE, LOW);
  displayDigit(8);
  delay(1000);
  digitalWrite(STROBE, HIGH);
  Serial.println(">> Strobe now HIGH, shall NOT display 0");
  displayDigit(0);
  delay(3000);
  digitalWrite(STROBE, LOW);
  Serial.println(">> Strobe now LOW, shall display A");
  displayDigit(10);
  
  Serial.println("Strobe test completed.");
}

void setup() {
  Serial.begin(9600);

  pinMode(INPUTA, OUTPUT);
  pinMode(INPUTB, OUTPUT);
  pinMode(INPUTC, OUTPUT);
  pinMode(INPUTD, OUTPUT);

  pinMode(LDECIMAL, OUTPUT);
  pinMode(RDECIMAL, OUTPUT);
  digitalWrite(LDECIMAL, HIGH);
  digitalWrite(RDECIMAL, HIGH);

  pinMode(STROBE, OUTPUT);
  pinMode(BLANKING, OUTPUT);
  
  digitalWrite(BLANKING, HIGH);
  digitalWrite(STROBE, LOW);

  Serial.println("TIL311 Test program v01.00");
  Serial.println("(c)2022, Claude \"Tryphon\" Théroux");
  Serial.println("Montréal, Québec, Canada");

  testPoints();
  testDigits();
  testBlanking();
  testStrobe();
}


void loop() {
}
