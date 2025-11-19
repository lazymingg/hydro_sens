const express = require('express')
const app = express()
const port = 3000
const user_router = require('./route/user')
const cors = require('cors')

app.use(cors({
  origin: 'http://localhost:5174', // allow to server to accept request from different origin
}));

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.use('/user', user_router)

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
