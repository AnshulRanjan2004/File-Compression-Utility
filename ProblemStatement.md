Project Title: File Compression Utility

Project Description:
You have been tasked with developing a file compression utility using C++ version 11. The program should allow the user to compress and decompress files using a simple compression algorithm. The compression algorithm should aim to reduce the file size while maintaining the ability to restore the original file.

Project Requirements:
1. User Interface:
   - The program should display a menu with the following options:
     1. Compress a file
     2. Decompress a file
     3. Exit the program
   - The program should repeatedly prompt the user for a menu choice until the user chooses to exit.

2. File Compression Algorithm:
   - The compression algorithm should be based on a simple method such as Run-Length Encoding (RLE) or Huffman coding.
   - If you choose RLE, it should replace sequences of repeated characters with a count and the corresponding character.
   - If you choose Huffman coding, it should generate a variable-length binary code for each character based on their frequency of occurrence in the file.
   - Ensure that the compressed file can be decompressed to restore the original file.

3. Compress a File:
   - When the user selects the option to compress a file, the program should prompt the user to enter the path to the file to be compressed.
   - The program should apply the chosen compression algorithm to the file, creating a compressed version of the file.
   - The program should provide appropriate feedback to the user after the compression process.

4. Decompress a File:
   - When the user selects the option to decompress a file, the program should prompt the user to enter the path to the file to be decompressed.
   - The program should apply the reverse process of the chosen compression algorithm to the file, restoring the original file.
   - The program should provide appropriate feedback to the user after the decompression process.

5. Error Handling:
   - The program should handle errors gracefully, such as invalid file paths, file format mismatches during decompression, or any other potential issues.
   - Provide meaningful error messages to guide the user in case of errors.

6. Performance Considerations:
   - While the main focus is on functionality, you can explore ways to optimize the compression algorithm or improve the overall performance of the program.
   - Consider testing the program with large files and measuring the compression ratio and execution time to assess its efficiency.

7. Documentation:
   - Include comments in the code to explain the purpose and functionality of major sections of your program.
   - Provide a brief overview of the program's functionality in a README file, including instructions on how to compile and run the program.

Note: You are not required to implement advanced compression algorithms like Lempel-Ziv-Welch (LZW) or DEFLATE. Focus on creating a functional program that provides basic file compression and decompression capabilities.
