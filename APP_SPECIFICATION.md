# Technical Specification

## About

This documentation describes the APDU messages interface to communicate with the Doom application.

The application covers the following functionalities :

  - Send a pause/quit message to the game
  - Send a play message to the game
  - Send player inputs to the game
  - Retrieve the Doom app version
  - Retrieve the Doom app name

The application interface can be accessed over HID or BLE

## APDUs

### Quit/Pause the game

#### Description

This command returns SW_OK (900) on Quit/Pause the game.

#### Coding

##### `Command`

| CLA | INS   | P1                                                 | P2    | Lc  |
| --- | ---   | ---                                                | ---   | --- |    
| D0  |  0D   |  06 : command to quit                               | 00    | 00 |


##### `Input data`

None
       
##### `Output data`

None

### Play/resume the game

#### Description

This command returns SW_OK (900) on Quit/Pause the game.

#### Coding

##### `Command`

| CLA | INS   | P1                                                 | P2    | Lc  |
| --- | ---   | ---                                                | ---   | --- |    
| D0  |  0D   |  07 : play the game command                               | 00    | 00 |


##### `Input data`

None
       
##### `Output data`

None


### SEND PLAYER INPUTS

#### Description

This command send player inputs in as data base on the following enum :
```C
UP = 0x05, 
DOWN = 0x06,
LEFT = 0x07,
RIGHT = 0x8,
FIRE = 0x0F
```

#### Coding

##### `Command`

| CLA | INS  | P1                   | P2                               | Lc       | Le       |
| --- | ---  | ---                  | ---                              | ---      | ---      |
| D0  | 0D   |  05: inputs command | 00 | variable | variable |


##### `Input data (first transaction data block)`

| Description                                          | Length   | 
| ---                                                  | ---      | 
| Inputs1     | 1        |
| Inputs2                  | 1        |
| ...                                                  | 1        |
| InputsN                  | 1        |
  
##### `Output data`

None                                                 


### GET APP VERSION

#### Description

This command returns boilerplate application version

#### Coding

##### `Command`

| CLA | INS | P1  | P2  | Lc   | Le |
| --- | --- | --- | --- | ---  | ---|
| E0  | 03  | 00  | 00  | 00   | 04 |

##### `Input data`

None

##### `Output data`

| Description                       | Length |
| ---                               | ---    |
| Application major version         | 01 |
| Application minor version         | 01 |
| Application patch version         | 01 |


### GET APP NAME

#### Description

This command returns boilerplate application name

#### Coding

##### `Command`
| CLA | INS | P1  | P2  | Lc   | Le |
| --- | --- | --- | --- | ---  | ---|
| E0  | 04  | 00  | 00  | 00   | 04 |

##### `Input data`

None

##### `Output data`
| Description           | Length   |
| ---                   | ---      |
| Application name      | variable |


## Status Words

The following standard Status Words are returned for all APDUs.

##### `Status Words`


| SW       | SW name                     | Description                                           |
| ---      | ---                         | ---                                                   |
|   6985   | SW_DENY	                   | Rejected by user                                      |
|   6A86   | SW_WRONG_P1P2               | Either P1 or P2 is incorrect                          |
|   6A87   | SW_WRONG_DATA_LENGTH        | Lc or minimum APDU length is incorrect                |
|   6D00   | SW_INS_NOT_SUPPORTED	       | No command exists with INS                            |
|   6E00   | SW_CLA_NOT_SUPPORTED        | Bad CLA used for this application                     |
|   B000   | SW_WRONG_RESPONSE_LENGTH    | Wrong response length (buffer size problem)           |
|   B007   | SW_BAD_STATE                | Security issue with bad state                         |
|   9000   | OK	                         | Success                                               |