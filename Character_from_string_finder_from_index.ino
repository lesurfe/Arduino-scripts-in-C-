// Arduino script to process a user-input string, convert it to a character array, and find the position (index) of each character in a pre-set list.

const char VALID_CHARS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '&', '!', '$', ',', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '}; // The pre-set list of characters to search within. Note: Arrays are zero-indexed
const int ARRAY_SIZE = sizeof(VALID_CHARS) / sizeof(VALID_CHARS[0]);

const int MAX_INPUT_LENGTH = 64; // Maximum size for the input character array (including the null terminator '\0')

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  
  Serial.println("Valid characters are: ");
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print(VALID_CHARS[i]); // Print the list of valid characters for the user
    Serial.print(" ");
  }

  Serial.println("\nAmount of characters available: ");
  Serial.println(ARRAY_SIZE);
  Serial.println("\nPlease input a string (up to 63 chars) and press 'Send' in the Serial Monitor.");
}

void loop() {
  // Check if any data has been sent from the Serial Monitor
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n'); // 1. Read the entire incoming line as a String object, stopping at the newline character ('\n')
    
    while (Serial.available()) {
      Serial.read(); // Clean up any stray carriage return characters that might be in the buffer
    }
    
    if (inputString.length() >= MAX_INPUT_LENGTH) {
      Serial.println("\nError: Input string is too long. Please limit to 63 characters."); // Check if the input string is too long
      Serial.println("\nReady for next input...");
      return; // Exit loop iteration
    }

    char inputCharArray[MAX_INPUT_LENGTH]; // 2. Convert the String object to a null-terminated character array
    inputString.toLowerCase(); // Convert the entire input string to lowercase
    inputString.toCharArray(inputCharArray, MAX_INPUT_LENGTH);
    
    Serial.print("\nProcessing input string: ");
    Serial.print(inputCharArray);
    Serial.print("\nInput string lenght: \"");
    Serial.print(inputString.length());
    Serial.println("\"");
    
    for (int j = 0; inputCharArray[j] != '\0'; j++) {
      char currentChar = inputCharArray[j]; // 3. Process each character in the input array
      bool found = false;

      // 4. Search for the current character in the VALID_CHARS array
      for (int i = 0; i < ARRAY_SIZE; i++) {
        if (VALID_CHARS[i] == currentChar) {
          Serial.print("  Character '");
          Serial.print(currentChar);
          Serial.print("' (Input Position: ");
          Serial.print(j);
          Serial.print(") found at VALID_CHARS Index: ");
          Serial.println(i);
          found = true;
          break; // Stop searching for this character
        }
      }

      // If the character was not found (and is not a space)
      if (!found && currentChar != ' ') {
        Serial.print("  Character '");
        Serial.print(currentChar);
        Serial.println("' is NOT in the valid list.");
      }
      
      // We explicitly skip spaces, but you can change this if needed
      if (currentChar == ' ') {
        Serial.println("  (Space skipped)");
      }
    }
    
    Serial.println("\nReady for next input...");
  }
  
  delay(100); 
}