void codegen();

void codegen() {
  int a = 42; /* a = -64 */
  a = a - 4; /* a = 4, *b = 4 */
  digitalWrite(28, HIGH);
  delay(a * 1000);
  digitalWrite(28, LOW);
  //delay(*b * 1000);
}