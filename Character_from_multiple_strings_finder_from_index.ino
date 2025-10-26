// Arduino script to process a user-input string, convert it to a character array,  and find the position (index) of each character in a pre-set list, storing the  results of up to 8 strings in a 2D array of indices.

const char VALID_CHARS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '&', '!', '$', ',', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '}; 
const int ARRAY_SIZE = sizeof(VALID_CHARS) / sizeof(VALID_CHARS[0]);

const int MAX_INPUT_LENGTH = 30; // Maximum size for the actual string content (30 characters)
// Total number of strings the user can input
const int MAX_STRINGS = 8;

char inputCharArray[MAX_INPUT_LENGTH + 1]; // Array to store the current user input string (30 chars + null terminator)

int storedIndices[MAX_STRINGS][MAX_INPUT_LENGTH]; // 2D Array to store the character index positions for each string. The structure is [String Index 0-7] [Character Index 0-29]

int stringCount = 0; // Counter to track which string the user is currently entering (0 to 7)

// --- FUNCTION 1: Handles serial reading, array preparation, and padding. Returns true if input was successfully read and prepared, false otherwise.
bool readAndPrepareInput() {
  String inputString = Serial.readStringUntil('\n'); // Function 1. Handles serial reading, array preparation, and padding. Returns true if input was successfully read and prepared, false otherwise.
  
  while (Serial.available()) {
    Serial.read(); // Clean up any stray carriage return characters that might be in the buffer
  }
  
  if (inputString.length() > MAX_INPUT_LENGTH) {
    Serial.println("\nError: Input string is too long. Please limit to 30 characters."); // Input validation: If the string is already too long
    return false; // Indicate failure
  }

  inputString.toLowerCase(); // Convert the input string to lowercase and copy it to the global char array
  int inputLen = inputString.length();
  inputString.toCharArray(inputCharArray, inputLen + 1); // Copy actual content and null terminator

  for (int i = inputLen; i < MAX_INPUT_LENGTH; i++) {
    inputCharArray[i] = ' ';
  }

  inputCharArray[MAX_INPUT_LENGTH] = '\0'; // Ensure the array is terminated right after the MAX_INPUT_LENGTH boundary
  
  Serial.print("\nProcessing String #");
  Serial.print(stringCount + 1);
  Serial.print(" (Padded Length: ");
  Serial.print(MAX_INPUT_LENGTH);
  Serial.println(")");
  
  return true; // Indicate success
}

// Function 2. Processes the prepared character array and stores indices
void processInputArray() {
  Serial.print("Input Content Preview: \""); // Print the first part of the padded array for confirmation
  for(int j = 0; j < 20; j++) { 
    Serial.print(inputCharArray[j]); 
  }
  Serial.println("...\"");

  // 3. Process each character in the padded input array (MAX_INPUT_LENGTH = 30 times)
  for (int j = 0; j < MAX_INPUT_LENGTH; j++) {
    char currentChar = inputCharArray[j];
    bool found = false;
    int charIndex = -1; // Default index value if not found

    // 4. Search for the current character in the VALID_CHARS array
    for (int i = 0; i < ARRAY_SIZE; i++) {
      if (VALID_CHARS[i] == currentChar) {
        charIndex = i; // Store the index of the character in VALID_CHARS
        found = true;
        break; // Stop searching for this character
      }
    }
    
    // Store the found index (or -1 if not found) into the 2D array
    // This is the core logic: storing the position of the character into the correct array (row)
    storedIndices[stringCount][j] = charIndex;
    
    // Simple error reporting for characters not in the VALID_CHARS list
    if (!found) {
        Serial.print("  WARNING: Character '");
        Serial.print(currentChar);
        Serial.println("' not in VALID_CHARS list. Stored -1.");
    }
  }
}

void setup() {
  Serial.begin(9600); 
  
  Serial.println("--- 8-String Index Processor ---");
  Serial.print("Valid characters list size: ");
  Serial.println(ARRAY_SIZE);
  
  Serial.println("Valid characters are (lowercase, symbols, digits, space):");
  
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print(VALID_CHARS[i]); // Print the list of valid characters for the user
    Serial.print(" ");
  }
  Serial.println("\n");
  
  Serial.print("Maximum strings allowed: ");
  Serial.println(MAX_STRINGS);
  Serial.print("Each string will be padded to ");
  Serial.print(MAX_INPUT_LENGTH);
  Serial.println(" characters.");
  
  Serial.print("\n>>> INPUT REQUEST: Please input String #1 (max 64 chars) and press 'Send'.");
}

void loop() {

  int f = 0;
  int c = 0;

  if (stringCount < MAX_STRINGS) {
    if (Serial.available() > 0) {
      // 1. Read input, convert, and pad
      if (readAndPrepareInput()) {
        // 2. Process the padded array and store the indices
        processInputArray();
        
        // 3. Increment the string counter
        stringCount++;
        
        if (stringCount < MAX_STRINGS) {
          // Request the next string
          Serial.print("\n>>> INPUT REQUEST: Please input String #");
          Serial.print(stringCount + 1);
          Serial.println(" (max 64 chars) and press 'Send'.");
        } else {
          // Process completed
          Serial.println("\n--- All 8 Strings Processed ---");
          Serial.println("The index data is now stored in the 2D array 'storedIndices'.");
          
          for (f = 0; f < 8; f++){
            Serial.print("String ");
            Serial.print(f);
            Serial.print(" : ");
            for (c = 0; c < 30; c++){
              Serial.print(storedIndices[f][c]);
              Serial.print(" ");
            }
            Serial.println();
          }
        }
      }
    }
  } 
  
  delay(100); 
}