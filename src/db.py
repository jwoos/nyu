import pymysql


connection = pymysql.connect(
    host='db',
    port=3306,
    user='user',
    password='password',
    db='evaluation',
    charset='utf8mb4',
    cursorclass=pymysql.cursors.DictCursor
)
