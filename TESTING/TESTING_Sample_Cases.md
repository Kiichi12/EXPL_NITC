# Quick-Start: Sample Test Cases to Create

## Setup Instructions

```bash
# 1. Create directory structure
mkdir -p root-dir/TESTING/{input,expected_output,output}

# 2. Copy the Makefile
cp TESTING_Makefile root-dir/TESTING/Makefile

# 3. Create sample test files (instructions below)
```

---

## STAGE 1: Expression Evaluation Test Cases

### Test 1.1: Single Number

```bash
# Create test input
cat > root-dir/TESTING/input/stage-1-case-1-compilation.txt << 'EOF'
3
EOF

# Create expected output (depends on your compiler output format)
# If your compiler outputs the generated XSM code:
cat > root-dir/TESTING/expected_output/stage-1-case-1-xsm.txt << 'EOF'
MOV R0, 3
MOV [4096], R0
INT 10
INT 5
INT 2
EOF
```

### Test 1.2: Simple Addition

```bash
cat > root-dir/TESTING/input/stage-1-case-2-compilation.txt << 'EOF'
3+2
EOF

cat > root-dir/TESTING/expected_output/stage-1-case-2-xsm.txt << 'EOF'
MOV R0, 3
MOV R1, 2
ADD R0, R1
MOV [4096], R0
INT 10
INT 5
INT 2
EOF
```

### Test 1.3: Complex Nested Expression

```bash
cat > root-dir/TESTING/input/stage-1-case-3-compilation.txt << 'EOF'
(3+2)+(5+6)
EOF

cat > root-dir/TESTING/expected_output/stage-1-case-3-xsm.txt << 'EOF'
MOV R0, 3
MOV R1, 2
ADD R0, R1
MOV R2, 5
MOV R3, 6
ADD R2, R3
ADD R0, R2
MOV [4096], R0
INT 10
INT 5
INT 2
EOF
```

### Test 1.4: With Parentheses

```bash
cat > root-dir/TESTING/input/stage-1-case-4-compilation.txt << 'EOF'
(42)
EOF

cat > root-dir/TESTING/expected_output/stage-1-case-4-xsm.txt << 'EOF'
MOV R0, 42
MOV [4096], R0
INT 10
INT 5
INT 2
EOF
```

---

## STAGE 2: Variables & I/O Test Cases

### Test 2.1: Simple Read and Write

```bash
cat > root-dir/TESTING/input/stage-2-case-1-compilation.txt << 'EOF'
begin
  read(a);
  write(a);
end
EOF

cat > root-dir/TESTING/input/stage-2-case-1-input.txt << 'EOF'
42
EOF

cat > root-dir/TESTING/expected_output/stage-2-case-1-runtime.txt << 'EOF'
42
EOF
```

### Test 2.2: Assignment and Output

```bash
cat > root-dir/TESTING/input/stage-2-case-2-compilation.txt << 'EOF'
begin
  a = 5;
  write(a);
end
EOF

cat > root-dir/TESTING/input/stage-2-case-2-input.txt << 'EOF'
EOF

cat > root-dir/TESTING/expected_output/stage-2-case-2-runtime.txt << 'EOF'
5
EOF
```

### Test 2.3: Multiple Variables

```bash
cat > root-dir/TESTING/input/stage-2-case-3-compilation.txt << 'EOF'
begin
  read(a);
  read(b);
  c = a + b;
  write(c);
end
EOF

cat > root-dir/TESTING/input/stage-2-case-3-input.txt << 'EOF'
10
20
EOF

cat > root-dir/TESTING/expected_output/stage-2-case-3-runtime.txt << 'EOF'
30
EOF
```

### Test 2.4: Expression with Precedence

```bash
cat > root-dir/TESTING/input/stage-2-case-4-compilation.txt << 'EOF'
begin
  a = 2;
  b = 3;
  c = a + b * 2;
  write(c);
end
EOF

cat > root-dir/TESTING/expected_output/stage-2-case-4-runtime.txt << 'EOF'
8
EOF
```

### Test 2.5: Overwriting Variables

```bash
cat > root-dir/TESTING/input/stage-2-case-5-compilation.txt << 'EOF'
begin
  a = 5;
  write(a);
  a = 10;
  write(a);
end
EOF

cat > root-dir/TESTING/expected_output/stage-2-case-5-runtime.txt << 'EOF'
5
10
EOF
```

---

## STAGE 3: Control Flow Test Cases

### Test 3.1: Simple IF-THEN

```bash
cat > root-dir/TESTING/input/stage-3-case-1-compilation.txt << 'EOF'
begin
  a = 5;
  if (a > 3) then
    write(1);
  endif
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-1-runtime.txt << 'EOF'
1
EOF
```

### Test 3.2: IF-THEN-ELSE (true condition)

```bash
cat > root-dir/TESTING/input/stage-3-case-2-compilation.txt << 'EOF'
begin
  a = 5;
  if (a > 3) then
    write(100);
  else
    write(200);
  endif
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-2-runtime.txt << 'EOF'
100
EOF
```

### Test 3.3: IF-THEN-ELSE (false condition)

```bash
cat > root-dir/TESTING/input/stage-3-case-3-compilation.txt << 'EOF'
begin
  a = 2;
  if (a > 5) then
    write(100);
  else
    write(200);
  endif
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-3-runtime.txt << 'EOF'
200
EOF
```

### Test 3.4: WHILE Loop

```bash
cat > root-dir/TESTING/input/stage-3-case-4-compilation.txt << 'EOF'
begin
  i = 0;
  while (i < 3) do
    write(i);
    i = i + 1;
  endwhile
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-4-runtime.txt << 'EOF'
0
1
2
EOF
```

### Test 3.5: Nested IF

```bash
cat > root-dir/TESTING/input/stage-3-case-5-compilation.txt << 'EOF'
begin
  a = 5;
  b = 10;
  if (a < 10) then
    if (b > 5) then
      write(1);
    endif
  endif
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-5-runtime.txt << 'EOF'
1
EOF
```

### Test 3.6: WHILE with Break (if implemented)

```bash
cat > root-dir/TESTING/input/stage-3-case-6-compilation.txt << 'EOF'
begin
  x = 0;
  while (1) do
    x = x + 1;
    write(x);
    if (x == 3) then
      break;
    endif
  endwhile
end
EOF

cat > root-dir/TESTING/expected_output/stage-3-case-6-runtime.txt << 'EOF'
1
2
3
EOF
```

---

## STAGE 4: Symbol Table & Type Checking

### Test 4.1: Valid Declaration (SUCCESS)

```bash
cat > root-dir/TESTING/input/stage-4-case-1-compilation.txt << 'EOF'
decl
  int a, b;
  str msg;
enddecl

begin
  a = 10;
  b = 20;
  msg = "hello";
  write(a);
  write(msg);
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-1-runtime.txt << 'EOF'
10
hello
EOF
```

### Test 4.2: Undeclared Variable (ERROR)

```bash
cat > root-dir/TESTING/input/stage-4-case-2-compilation.txt << 'EOF'
decl
  int x;
enddecl

begin
  y = 5;
  write(y);
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-2.err << 'EOF'
[ERROR] Undeclared variable 'y'
EOF
```

### Test 4.3: Redeclaration (ERROR)

```bash
cat > root-dir/TESTING/input/stage-4-case-3-compilation.txt << 'EOF'
decl
  int a;
  int a;
enddecl

begin
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-3.err << 'EOF'
[ERROR] Variable 'a' already declared
EOF
```

### Test 4.4: Type Mismatch in Assignment (ERROR)

```bash
cat > root-dir/TESTING/input/stage-4-case-4-compilation.txt << 'EOF'
decl
  int a;
  str msg;
enddecl

begin
  a = "hello";
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-4.err << 'EOF'
[ERROR] Type mismatch in assignment
EOF
```

### Test 4.5: Type Mismatch in Arithmetic (ERROR)

```bash
cat > root-dir/TESTING/input/stage-4-case-5-compilation.txt << 'EOF'
decl
  int a;
  str msg;
enddecl

begin
  msg = "test";
  a = msg + 5;
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-5.err << 'EOF'
[ERROR] Type mismatch in operation
EOF
```

### Test 4.6: String Variable Read/Write

```bash
cat > root-dir/TESTING/input/stage-4-case-6-compilation.txt << 'EOF'
decl
  str name;
enddecl

begin
  name = "Alice";
  write("Name: ");
  write(name);
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-6-runtime.txt << 'EOF'
Name: 
Alice
EOF
```

### Test 4.7: All 26 Variables

```bash
cat > root-dir/TESTING/input/stage-4-case-7-compilation.txt << 'EOF'
decl
  int a, b, c, d, e, f, g, h, i, j, k, l, m;
  int n, o, p, q, r, s, t, u, v, w, x, y, z;
enddecl

begin
  a = 1;
  z = 26;
  write(a);
  write(z);
end
EOF

cat > root-dir/TESTING/expected_output/stage-4-case-7-runtime.txt << 'EOF'
1
26
EOF
```

---

## ONE-COMMAND SETUP

Copy and paste this entire block to create all test cases at once:

```bash
#!/bin/bash

# Create directories
mkdir -p root-dir/TESTING/{input,expected_output,output}
cd root-dir/TESTING

# STAGE 1 TESTS
cat > input/stage-1-case-1-compilation.txt << 'EOF'
3
EOF
echo "MOV R0, 3
MOV [4096], R0
INT 10
INT 5
INT 2" > expected_output/stage-1-case-1-xsm.txt

cat > input/stage-1-case-2-compilation.txt << 'EOF'
3+2
EOF
echo "MOV R0, 3
MOV R1, 2
ADD R0, R1
MOV [4096], R0
INT 10
INT 5
INT 2" > expected_output/stage-1-case-2-xsm.txt

# STAGE 2 TESTS
cat > input/stage-2-case-1-compilation.txt << 'EOF'
begin
  read(a);
  write(a);
end
EOF
echo "42" > input/stage-2-case-1-input.txt
echo "42" > expected_output/stage-2-case-1-runtime.txt

cat > input/stage-2-case-2-compilation.txt << 'EOF'
begin
  a = 5;
  write(a);
end
EOF
echo "5" > expected_output/stage-2-case-2-runtime.txt

cat > input/stage-2-case-3-compilation.txt << 'EOF'
begin
  read(a);
  read(b);
  c = a + b;
  write(c);
end
EOF
echo -e "10\n20" > input/stage-2-case-3-input.txt
echo "30" > expected_output/stage-2-case-3-runtime.txt

# STAGE 3 TESTS
cat > input/stage-3-case-1-compilation.txt << 'EOF'
begin
  a = 5;
  if (a > 3) then
    write(1);
  endif
end
EOF
echo "1" > expected_output/stage-3-case-1-runtime.txt

cat > input/stage-3-case-2-compilation.txt << 'EOF'
begin
  a = 5;
  if (a > 3) then
    write(100);
  else
    write(200);
  endif
end
EOF
echo "100" > expected_output/stage-3-case-2-runtime.txt

cat > input/stage-3-case-3-compilation.txt << 'EOF'
begin
  a = 2;
  if (a > 5) then
    write(100);
  else
    write(200);
  endif
end
EOF
echo "200" > expected_output/stage-3-case-3-runtime.txt

cat > input/stage-3-case-4-compilation.txt << 'EOF'
begin
  i = 0;
  while (i < 3) do
    write(i);
    i = i + 1;
  endwhile
end
EOF
echo -e "0\n1\n2" > expected_output/stage-3-case-4-runtime.txt

# STAGE 4 TESTS
cat > input/stage-4-case-1-compilation.txt << 'EOF'
decl
  int a, b;
  str msg;
enddecl

begin
  a = 10;
  b = 20;
  msg = "hello";
  write(a);
  write(msg);
end
EOF
echo -e "10\nhello" > expected_output/stage-4-case-1-runtime.txt

cat > input/stage-4-case-2-compilation.txt << 'EOF'
decl
  int x;
enddecl

begin
  y = 5;
end
EOF
echo "[ERROR] Undeclared variable 'y'" > expected_output/stage-4-case-2.err

cat > input/stage-4-case-3-compilation.txt << 'EOF'
decl
  int a;
  int a;
enddecl

begin
end
EOF
echo "[ERROR] Variable 'a' already declared" > expected_output/stage-4-case-3.err

cat > input/stage-4-case-4-compilation.txt << 'EOF'
decl
  int a;
  str msg;
enddecl

begin
  a = "hello";
end
EOF
echo "[ERROR] Type mismatch" > expected_output/stage-4-case-4.err

echo "✓ All test cases created successfully!"
echo "Run: make test (in TESTING/)"
```

---

## Testing

```bash
cd root-dir/TESTING

# Run all tests
make test

# Run specific stage
make test-stage-1
make test-stage-2
make test-stage-3
make test-stage-4

# View help
make help

# Clean output
make clean
```

---

## Expected Output

```
==========================================
STAGE 1: Expression Evaluation
==========================================
Test: stage-1-case-1 [PASS]
Test: stage-1-case-2 [PASS]
-------------------------------------------
Stage 1 Results: TOTAL=2 PASS=2 FAIL=0

==========================================
STAGE 2: Variables & I/O
==========================================
Test: stage-2-case-1 [PASS]
Test: stage-2-case-2 [PASS]
Test: stage-2-case-3 [PASS]
-------------------------------------------
Stage 2 Results: TOTAL=3 PASS=3 FAIL=0

... (Stage 3 & 4 similarly)

==========================================
ALL STAGES TESTING COMPLETE
==========================================
```

This setup is now ready to use!
