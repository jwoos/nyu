import pymysql


connection = pymysql.connect(
    host='db',
    user='root',
    password='password',
    db='rating',
    charset='utf8mb4',
    cursorclass=pymysql.cursors.DictCursor
)
