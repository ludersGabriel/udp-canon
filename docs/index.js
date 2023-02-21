function getLogsPath(baseName) {
  const logsPath = []
  totalClients.forEach(
    (totalClient) => {
      totalMessages.forEach(
        (totalMessage) => {
          for (let i = 1; i <= 4; i++)
            logsPath.push(`logs/${baseName}-${totalClient}-${totalMessage}-${i}.log`)
        }
      )
    }
  )

  return logsPath
}

const clientDiv1 = document.getElementById('clientLogs1')
const serverDiv1 = document.getElementById('serverLogs1')

const totalMessages = [
  1000,
  10000,
  50000,
  100000,
  250000,
  500000,
  750000,
  1000000,
  2000000,
]

const totalClients = [
  1
]

const clientTeste1 = getLogsPath('client/teste1/client').map(
  (path) => {
    const a = document.createElement('a')
    a.href = path
    a.text = path.split('/')[3]

    return a
  }
)
const serverTeste1 = getLogsPath('server/teste1/server').map(
  (path) => {
    const a = document.createElement('a')
    a.href = path
    a.text = path.split('/')[3]

    return a
  }
)

clientTeste1.forEach(
  (a) => {
    clientDiv1.appendChild(a)
  }
)

serverTeste1.forEach(
  (a) => {
    serverDiv1.appendChild(a)
  }
)