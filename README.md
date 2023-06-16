<!DOCTYPE html>
<html>
<head>
  <title>Automatic Grading System</title>
  <style>
    body {
      font-family: Arial, sans-serif;
    }
    h1 {
      color: #333;
    }
    h2 {
      color: #666;
    }
    pre {
      background-color: #f5f5f5;
      padding: 10px;
      border-radius: 5px;
    }
    code {
      font-family: Consolas, monospace;
    }
  </style>
</head>
<body>
  <h1>Automatic Grading System</h1>

  <p>This is an automatic grading system that runs on Ubuntu and is written in the C programming language.</p>

  <h2>Ex2.2</h2>

  <p>Ex2.2 is a code that handles student submissions. It takes the following arguments:</p>

  <pre><code>./ex2.2 &lt;config_file&gt;</code></pre>

  <p>The <code>config_file</code> is a text file that should contain the following three lines:</p>

  <pre><code>&lt;folder_path&gt;
&lt;input_path&gt;
&lt;correct_output_path&gt;</code></pre>

  <p><code>&lt;folder_path&gt;</code> is the path to the folder that contains all the student folders. Each student folder should contain their submitted code.</p>
  <p><code>&lt;input_path&gt;</code> is the path to the text file that contains the input for the code.</p>
  <p><code>&lt;correct_output_path&gt;</code> is the path to the text file that contains the expected correct output.</p>

  <p>The program compiles and runs each student's code, comparing the output with the correct output using the code from ex21. It then assigns grades based on the comparison results.</p>

  <p>During the execution of ex2.2, several important concepts are utilized:</p>

  <ul>
    <li><strong>Input Redirection:</strong> The program reads the input for each student's code from the specified input file by redirecting the file as standard input using the <code>&lt;</code> operator.</li>
    <li><strong>Output Redirection:</strong> The program redirects the output of each student's code to a temporary file using the <code>&gt;</code> operator. This allows for easy comparison of the output with the correct output file.</li>
    <li><strong>Fork:</strong> The program utilizes the <code>fork()</code> system call to create child processes. Each child process is responsible for compiling and executing a student's code.</li>
  </ul>

  <h2>Ex21</h2>

  <p>Ex21 is a utility code used by ex2.2 to compare if two text files are identical.</p>
  
  <pre><code>// C code for ex21</code></pre>

  <p>It provides the function <code>are_files_identical</code> that compares two text files and returns whether they are identical or not.</p>

  <h2>Instructions</h2>

  <p>To compile and run the programs:</p>

  <pre><code>$ gcc ex2.2.c -o ex2.2
$ gcc ex21.c -o ex21
$ ./ex2.2 config.txt</code></pre>

  <p>Make sure you have the required input files and folder structure as specified in the config file.</p>

  <h2>License</h2>

  <p>This project is licensed under the MIT License. See the <code>LICENSE</code> file for details.</p>
</body>
</html>
