int main (int DUMMY)
/* simple tests of silly syntax errors */
{
   int x,y,z; /* ERROR here: colon instead of a comma */

   float p;

   /* this is syntactically correct, but will fail the type checking in the next compiler project stage */
   p = -z * (x/345+y*1.0) + - 300;
   p = -z * (x/345+y*1.0) + -300; /* notice that both lines are legal, but they mean slightly different things */

   while (p>=-(x+y)*3.45/6-z)
     z = z + 3;

   /* what happens if we skip a parentheses? ERROR here */
   while (p>=-(x+y)*3.45/6-z
     z = z + 3;

}
