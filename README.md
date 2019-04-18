# Lexy

Lexy is a Lexical Analyser which creates tokens classified in the following grammemes:

- Reserved words
- Identifiers
- Constants (numerical, single characters and strings)
- Common operators (assignment, arithmetic, logic and relational)
- Grouping symbols
- Punctuation marks
- Comments

## Transition Function

Lexy uses a matrix to determine its next state. The transition matrix is as follows:

> Insert matrix here

### Codes for delimiting states

The Final/Non final tag determines whether if the last symbol read by the automata is the final one in the current lexeme. or if it corresponds to a new token.

When reaching an accepting state with a final symbol, the automata appends it to the current lexeme and creates a new token. Afterwards, it devolves to the initial state and continues analysing the string of symbols beggining with the next one.

In the case of a non final symbol, the automata creates a token with the current lexeme and returns to the initial state keeping the symbol for a new lexeme.

#### 100s - Accepting states

| Code | Grammeme       | Final     |
| ---- | -------------- | --------- |
| 101  | Reserved word  | Non final |
| 102  | Identifier     | Non final |
| 103  | Commentary     | Final     |
| 104  | Integer        | Non final |
| 105  | Float          | Non final |
| 106  | Float Exponent | Non final |
| 107  | Character      | Final     |
| 108  | String         | Final     |
| 109  | Multiplication | Non final |
| 110  | Division       | Non final |
| 111  | Addition       | Non final |
| 112  | Substraction   | Non final |
| 113 | Modulo                | Non final |
| 114 | Logical OR            | Non final |
| 115 | Logical AND           | Non final |
| 116 | Logical NOT           | Non final |
| 117 | Less than             | Non final |
| 118 | Less than or equal    | Non final |
| 119 | Greater than          | Non final |
| 120 | Greater than o equal  | Non final |
| 121 | Equals                | Non final |
| 122 | Is different          | Non final |
| 123 | Assignment            | Non final |
| 124 | Point                 | Non final |
| 125 | Comma                 | final     |
| 126 | Colon                 | Non final |
| 127 | Semi-colon            | final     |
| 128 | Open parenthesis      | final     |
| 129 | Close parenthesis     | final     |
| 130 | Open brackets         | final     |
| 131 | Close brackets        | final     |
| 132 | Open square brackets  | final     |
| 133 | Close square brackets | final     |


#### 500s - Rejecting states

| Code | Error         |
| ---- | ------------- | 
| 501  | Identifiers can not end with a '_' |
| 502  | Malformed float constant, expected a number after the point |
| 503  | Malformed float constant, expected a sign or a number after the exponent |
| 504  | Malformed character, expected an apostrophe |
| 505	 | Malformed OR operatoror, expected a second "|" |
| 506	 | Malformed AND operatoror, expected a second & |


