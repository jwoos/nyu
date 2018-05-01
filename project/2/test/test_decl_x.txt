/* trying to imagine all possible things that can go wrong with the symbol table.
   testing mostly declarations */

int y;
int y; /* redeclaring y */
float y; /* redeclaring y with different type */

int i2i (int);
float i2f(int);

int i2i (float); /* redeclaring i2i with different signature */

int i2i; /* redeclaring a function as a variable */

float main (float z)
{ int x; /* OK */
  int x; /* redeclaring a local */

  int y;
  float y; /* redeclaring a local with different type */

  float z;
  
  x=7+y;
  write inc(x); /* eventually, this should check for the signature of INC: types of the argument and return value */

  /* so that the following are both wrong */
  x = inc(z); /* wrong parameter type */
  z = inc(x); /* returns INT, assigned to float */
}

/* definitions with mismatched signature; all three are wrong */
float i2f (float x) {}
int i2f (int x) {}
int i2f (float x) {}

/* this one is correct */
float i2f (int x) { write "I have no idea what to do with x=", x; }

int inc(int x)
{
   /* inside inc */
   return x+1;
}
