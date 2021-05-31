function addError(error) {
    document.getElementById(ERRORS_P_ID).innerText += (error + '\n')
}

function clearErrors() {
    document.getElementById(ERRORS_P_ID).innerText = "";
}

function isMoveValid(startPos, endPos) {
    const isStartPosValid = validatePos(startPos, "start")
    const isEndPosValid = validatePos(endPos, "end")

    if (isStartPosValid && isEndPosValid) {
        if (startPos != endPos) {
            return true
        } else {
            addError("Start and end positions cannot be the same.")
        }
    }
    return false
}

function validatePos(pos, posType) {
    if (pos.length == 2) {
        if (pos[0] >= 'A' && pos[0] <= 'H' && pos[1] >= 1 && pos[1] <= 8) {
            return true
        }
    }
    addError(`Invalid ${posType} position: "${pos}".`)
    return false
}

function fromPosToByte(pos) {
    String.fromCharCode((pos[0] - 'A' + 1) * (pos[1]) - 1)
}

function setupNextPlayer() {
    if (player == "White") {
        setPlayer("Black", "black")
    } else {
        setPlayer("White", "white")
    }
}

function setPlayer(text, color) {
    player = text
    document.getElementById(PLAYER_ON_THE_MOVE).textContent = text
    document.getElementById(PLAYER_ON_THE_MOVE).style.color = color
}
