let totalTime = 0;
let timer;

function startTimer() {
    timer = setInterval(() => {
        totalTime += 1; // Incrementa o tempo em segundos
        if (totalTime % 1800 === 0) { // A cada 30 minutos
            sendNotification();
        }
    }, 1000);
}

function sendNotification() {
    chrome.notifications.create({
        type: "basic",
        iconUrl: "icon.png",
        title: "Hora de uma pausa!",
        message: "Você está navegando há 30 minutos. Lembre-se de descansar!",
        priority: 2
    });
}

chrome.tabs.onActivated.addListener(() => {
    if (!timer) {
        startTimer();
    }
});

chrome.tabs.onRemoved.addListener(() => {
    if (chrome.tabs.query({active: true}).length === 0) {
        clearInterval(timer);
        timer = null;
    }
});
