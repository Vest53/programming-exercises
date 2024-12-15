let totalTime = 0;
let timer;
let notificationInterval = 30; // Padrão de 30 minutos

function startTimer() {
    timer = setInterval(() => {
        totalTime += 1; // Incrementa o tempo em segundos
        if (totalTime % (notificationInterval * 60) === 0) { // Verifica o intervalo em segundos
            sendNotification();
        }
    }, 1000);
}

function sendNotification() {
    chrome.notifications.create({
        type: "basic",
        iconUrl: "icon.png",
        title: "Hora de uma pausa!",
        message: `Você está navegando há ${notificationInterval} minutos. Lembre-se de descansar!`,
        priority: 2
    });
}

// Carregar o intervalo de notificação ao iniciar
chrome.storage.sync.get('notificationInterval', (data) => {
    notificationInterval = data.notificationInterval || 30; // Padrão de 30 minutos
});

// Inicia o timer quando a extensão é ativada
chrome.runtime.onInstalled.addListener(startTimer);
chrome.tabs.onActivated.addListener(() => {
    if (!timer) {
        startTimer();
    }
});
