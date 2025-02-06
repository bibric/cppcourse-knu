#include "PrintHelper.h"

/* *************************************
 * * Fundamental types and expressions *
 * *************************************
 *
 * Tasks:
 * ------
 * - Compile the program and analyse the output of the different expressions
 * - Discuss with other students or your tutor in case the result of an expression is a surprise
 * - Fix the marked expressions by changing types such that they produce meaningful results
 * - Answer the questions in the code
 */

int main() {
  std::cout << "Using literals of different number types:\n";
  print(5);
  print(5.f/2);           //FIXME Если одна часть будет флоат то и результат тоже, не будет откидываться 0.5
  print(100/2ull);
  print(2 + 4ull);
  print(2.f + 4ull);
  print(0 - 1);       // FIXME u отвечает за то что б int был от 0 до 4294967295, а нам походу надо от -2 147 483 648 до 2 147 483 647
  print(1.0000000001L); // FIXME Why is this number not represented correctly? Перевод в добл и лонг дабл решает вывод с точностью выше 7го знака
  print(1.l + 1.e-18);   // FIXME Лонг дабл может решить, но у меня именно 18 знаков не сможет, так как точность вычислений не позволит "value=1.000000000100000008274037"

  std::cout << "\nUsing increment and decrement operators:\n";
  int a = 1;
  int b;
  int c;
  print(b = a++);       // Q: What is the difference between a++ and ++a?
  print(c = ++a);       //++а сначала увеличивает а и потом делает с как а. А а++ это сначала назначить с а потом увеличить а
  print(a);
  print(b);
  print(c);

  std::cout << "\nCompound assignment operators:\n";
  int n = 1;
  print(n *= 2);        // Q: Is there a difference between this and the next line?
  print(n *= 2.9);      // в строке 38 мы умножаем 1 на 2 и выводим 2. В строке 39 умножаем уже 2 на 2.9 выводя целое число
  print(n -= 1.1f);
  print(n /= 4);        // Q: Based on the results of these expressions, is there a better type to be used for n?
                        //надо изначально эн сделать не инт а хотя б флоат так как многие умножения и деления просто откидывают дробную часть
  std::cout << "\nLogic expressions:\n";
  const bool alwaysTrue = true;
  bool condition1 = false;
  bool condition2 = true;
  print( alwaysTrue && condition1 && condition2 );
  print( alwaysTrue || condition1 && condition2 );  // Q: Why does operator precedence render this expression useless?
  print( alwaysTrue && condition1 || condition2 );  // две палки вроде считаються последними
  print(condition1 != condition1);                  // Q: What is the difference between this and the following expression?
  print(condition2 = !condition2);                  //знак восклицания привращает в противовположный
  print( alwaysTrue && condition1 && condition2 );
  print( alwaysTrue || condition1 && condition2 );
  print( alwaysTrue && condition1 || condition2 );

  std::cout << '\n';
  print( false || 0b10 );     // Q: What is the difference between || and | ?
  print( false | 0b10 );        //первое логичное второе битовое
  printBinary( 0b1 & 0b10 );
  printBinary( 0b1 | 0b10 );
  printBinary( 0b1 && 0b10 ); // Q: Are the operators && and || appropriate for integer types?
  printBinary( 0b1 || 0b10 );//1 в битовой системе это нули и 1 вконце. В двух операциях нет 0 поэтому ответ каждой тру или 1

  std::cout << "\nPlay with characters and strings:\n";
  print("a");                 // Q: Why is this expression two bytes at run time, the next only one?
  print('a');                   //стринг="" имеет вконце \0, а один символ это ''

  char charArray[20];
  char* charPtr = charArray;
  charArray[19] = 0; // Make sure that our string is terminated with the null byte

  print(charArray);
  print(charArray[0] = 'a');
  print(charArray);
  print(charArray[1] = 99);//98 это b, 99 это с
  print(charArray);
  print(charPtr);
  // FIXME: Ensure that no unexpected garbage is printed above
  //та нет мусора
}
