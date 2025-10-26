// Arduino script to find the position (index) of a user-input character 

const char VALID_CHARS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '€', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '}; // The pre-set list of characters to search within. Note: Arrays are zero-indexed
const int ARRAY_SIZE = sizeof(VALID_CHARS) / sizeof(VALID_CHARS[0]);

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  
  Serial.println("Valid characters are: ");
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print(VALID_CHARS[i]); // Print the list of valid characters for the user
    Serial.print(" ");
  }

  Serial.println("\nAmount of characters available: ");
  Serial.println(ARRAY_SIZE);
  Serial.println("\nPlease input a single character and press 'Send' in the Serial Monitor.");
}

void loop() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read(); // Read the incoming character from the user
    
    inputChar = tolower(inputChar); // Convert the input to lowercase to match the list, just in case the user uses uppercase
    
    while (Serial.available()) {
      Serial.read(); // Clean up any extra newline or carriage return characters that might be in the buffer
    }

    bool found = false; // Flag to track if the character was found

    // Iterate through the array to find a match
    for (int i = 0; i < ARRAY_SIZE; i++) {
      if (VALID_CHARS[i] == inputChar) {
        Serial.print("\nFound character '");
        Serial.print(inputChar);
        Serial.print("' at index: ");
        Serial.println(i);
        found = true;
        break; // Exit the loop once the character is found
      }
    }

    if (!found) {
      Serial.print("\nError: Character '");
      Serial.print(inputChar);
      Serial.println("' is not in the list. Try again.");
    }
    
    Serial.println("\nReady for next input...");
  }
  
  // Short delay to avoid constantly checking Serial.available()
  delay(100); 
}
