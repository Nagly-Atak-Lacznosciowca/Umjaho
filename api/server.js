const express = require('express')
const app = express()
const port = 3000

app.use(express.json());

const users = []

function newUser(login, password) {
    return {
        login: z,
        password: password,
        registered: Date.now()
    }
}

app.post('/register', (req, res) => {
    // console.log(requestJSON)
    console.log(req.body)

})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
