# OAuth

## 1.0 与 2.0
oauth1.0 
one-legged
two-legged
three-legged
echo
xAuth

oauth2.0

two-legged
three-legged

## OAuth2.0中的角色

1. Client 第三方应用(贵邮)
2. Resurce Owner 资源所有者，即用户（我）
3. Authorization Server 授权服务器，即提供第三方登录的服务器（北邮人论坛服务器）
4. Resource Server 用户资源信息的服务器，通常和Authorization Server属于同一应用（北邮人论坛服务器）

## OAtuh2.0模式

1. 授权码模式(grant_type = code)
2. 简化模式(grant_type = token)
   不产生code给Client，而是在redirect_uri（Resource Server）中在hash部分(#) 带上access_token，注意hash部分在发送请求时是不带的。Resource Server返回脚本 用来提取hash中的access token ，浏览器把token发送给client
3. 密码模式(grant_type = password)
   用户告知客户端用户名密码 有客户端直接向Authorization Server 发送POST请求 获得access_token
4. 客户端模式(grant_type = clientcredentials)

## 更新令牌
refresh_token grant_type=refresh_token
   

