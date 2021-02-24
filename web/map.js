var map = new BMapGL.Map("container");
// 创建地图实例
var point = new BMapGL.Point(116.404, 39.915);
// 创建点坐标
map.centerAndZoom(point, 15);
// 初始化地图，设置中心点坐标和地图级别
var scaleCtrl = new BMapGL.ScaleControl();  // 添加比例尺控件
map.addControl(scaleCtrl);
var zoomCtrl = new BMapGL.ZoomControl();  // 添加比例尺控件
map.addControl(zoomCtrl);
map.enableScrollWheelZoom(true);     //开启鼠标滚轮缩放
var context;
// 初始化Qt连接
function init()
{
    if (typeof qt != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
        context = channel.objects.bmapBridge;
        }
        );
    }
    else
    {
        alert("qt对象获取失败！");
    }
}
// 向qt发送坐标消息
function setCoordinate(x, y)
{
    if(typeof context == 'undefined')
    {
        alert("context对象获取失败！");
    }
    else
    {
        context.setCoordinate(x, y);
    }
}
init();
map.addEventListener('click', function (e) {
    //alert('点击位置经纬度：' + e.latlng.lng + ',' + e.latlng.lat);
    setCoordinate(e.latlng.lng, e.latlng.lat);
});
