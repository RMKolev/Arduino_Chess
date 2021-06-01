const SUBMIT_BUTTON_ID = "submit-button"
const START_POS_ID = "start-pos"
const END_POS_ID = "end-pos"
const ERRORS_P_ID = "errors"
const PLAYER_ON_THE_MOVE = "player-on-the-move"

var player = ""

window.addEventListener('load', () => {
    const espUrl = 'http://192.168.88.222'

    setupStream(espUrl)
    setupSubmitButton(espUrl)
    setPlayer("White", "white")
})

function setupStream(espUrl) {
    const stream = document.getElementById('stream')
    const streamContainer = document.getElementById('stream-container')

    stream.src = `${espUrl}:81/stream`
}

function setupSubmitButton(espUrl) {
    document.getElementById(SUBMIT_BUTTON_ID).addEventListener("click",
        function () {
            clearErrors();

            const startPos = document.getElementById(START_POS_ID).value
            const endPos = document.getElementById(END_POS_ID).value

            if (isMoveValid(startPos, endPos)) {
                sendMove(espUrl, startPos, endPos)
                setupNextPlayer()
            }
        })
}


function sendMove(espUrl, startPos, endPos) {
    const encodedMove = fromPosToByte(startPos) + fromPosToByte(endPos);
    const moveCommand = `${espUrl}/control?var=move&val=${encodedMove}`
    fetch(moveCommand).
        then(res => {
            console.log(`Status code from command: ${moveCommand}: ${res.status}`)
        })
}
