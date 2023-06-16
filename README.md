# autumatic-grading-system
<!DOCTYPE html>
<html>
<head>
  <title>Automatic Grading System - README</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      line-height: 1.6;
      padding: 20px;
    }

    h1, h2 {
      margin-top: 40px;
    }

    code {
      font-family: Consolas, monospace;
      font-size: 14px;
      background-color: #f5f5f5;
      padding: 2px 4px;
    }

    pre {
      font-family: Consolas, monospace;
      background-color: #f5f5f5;
      padding: 10px;
      overflow-x: auto;
    }

    ul {
      padding-left: 20px;
    }
  </style>
</head>
<body>
  <h1>Automatic Grading System</h1>
  <p>This repository contains an automatic grading system for evaluating student submissions. The system is built using the C programming language and runs on Ubuntu.</p>

  <h2>System Requirements</h2>
  <ul>
    <li>Ubuntu operating system</li>
    <li>C compiler (GCC)</li>
  </ul>

  <h2>File Descriptions</h2>
  <ul>
    <li><code>ex21.c</code>: This file contains the code for comparing two text files and checking if they are identical. It is used by the grading system.</li>
    <li><code>ex2.2.c</code>: This file is the main component of the grading system. It compiles and runs the students' code, compares the output with the expected output, and assigns grades based on the comparison.</li>
  </ul>

  <h2>Usage</h2>
  <p>The grading system takes a text file as input, which should contain the following information on separate lines:</p>
  <pre>
    &lt;path_to_folder&gt;        # Path to the folder containing all the students' folders
    &lt;path_to_input&gt;         # Path to the text file for input
    &lt;path_to_correct_output&gt; # Path to the correct output file
  </pre>

  <p>To run the grading system, execute the following command:</p>
  <pre>
    $ ./ex2.2 &lt;input_file&gt;
  </pre>

  <h2>Explanation of ex2.2</h2>
  <p><code>ex2.2.c</code> is responsible for handling the student submissions, compiling their code, running it, and comparing the output with the expected output. Here's a brief overview of its functionality:</p>
  <ul>
    <li>The program reads the input file provided and extracts the necessary paths for the student submissions, input, and correct output files.</li>
    <li>It traverses the student folders and handles each submission individually.</li>
    <li>For each student, it compiles their C code using GCC and checks for any compilation errors.</li>
    <li>If the code compiles successfully, it runs the executable and redirects the input and output streams.</li>
    <li>The program then compares the output with the expected output using the <code>comp.out</code> program.</li>
    <li>Based on the comparison results, it assigns grades to the students.</li>
    <li>The grading results, including student names and grades, are written to the <code>results.csv</code> file.</li>
    <li>Any compilation errors or runtime errors encountered during the grading process are recorded in the <code>errors.txt</code> file.</li>
  </ul>

  <h2>Customization</h2>
  <p>You can customize the code to suit your specific needs. For example, you can modify the grading criteria, handle different types of student submissions, or extend the functionality of the system.</p>

  <h2>Disclaimer</h2>
  <p>Please note that this automatic grading system serves as a starting point and may require additional modifications and improvements to fit your particular use case. It is important to thoroughly test and validate the system before using it in a production environment.</p>
</body>
</html>
