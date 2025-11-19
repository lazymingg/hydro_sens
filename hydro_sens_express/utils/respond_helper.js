function success(res, data = {}, message = "OKEEEEEE")
{
    return res.send({
        status: "success",
        message: message,
        data: data
    })
}

function error(res, data = {}, message = "oh no....")
{
    return res.send({
        status: "oh no ....",
        message: message,
        data: data
    })
}

module.exports = {
    success,
    error
}